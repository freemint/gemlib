/* Process & thread functions
 */

/*  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

# include <st-out.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <mint/dcntl.h>
# include <mint/mintbind.h>

# include "gemma.h"
# include "dosproto.h"
# include "proc.h"

# define SMS_JUSTSEND	0
# define SMS_REPLSEND	1
# define SMS_PID2APID	0x8000

static const char selfname[] = "u:\\proc\\.-1";
static const char smsname[] = "u:\\pipe\\sms";

typedef struct
{
	ushort command;
	short destproc;
	short length;
	short res[5];
	short msg[8];
} SMSBLK;

INLINE long
smswrite(PROC_ARRAY *proc, SMSBLK *smsblk)
{
	long file, r;

	file = r = _open(proc, smsname, O_WRONLY|O_DENYNONE);
	if (r < 0)
		return r;
	r = _write(proc, file, sizeof(SMSBLK), (void *)smsblk);
	_close(proc, file);

	return 0;
}

static void
sig_child(void)
{
	short pid = Pgetpid();
	long p;
	SMSBLK sms;
	PROC_ARRAY *proc;

	proc = pidtable[pid];

	p = _wait3(proc, 1, 0L);
	if (p == 0)
		return;
	bzero(&sms, sizeof(SMSBLK));

	sms.command = (ushort)(SMS_JUSTSEND|SMS_PID2APID);
	sms.destproc = pid;
	sms.length = 16;
	sms.msg[0] = CH_EXIT;
	sms.msg[1] = 0;
	sms.msg[2] = 0;
	sms.msg[3] = (short)(p>>16);
	sms.msg[4] = (short)p;
	smswrite(proc, &sms);
}

INLINE long
getprgflags(PROC_ARRAY *proc)
{
	long file, r, flags;

	file = r = _open(proc, selfname, O_RDONLY);
	if (r < 0)
		return (F_FASTLOAD | F_ALTLOAD | F_ALTALLOC);
	r = _cntl(proc, file, &flags, PGETFLAGS);
	_close(proc, file);
	if (r < 0)
		return (F_FASTLOAD | F_ALTLOAD | F_ALTALLOC);

	return flags;
}

/* Like Pexec(), but:
 *
 * - searches through $PATH
 * - runs scripts
 * - accepts command tail as C string of any length (limited by free mem)
 * - constructs ARGV out of it.
 *
 * `flags' is a bitfield:
 * 0 - redirect stdout to /dev/null
 * 1 - redirect stderr to /dev/null
 * 2 - register SIGCHLD handler
 *
 */

long
proc_exec(BASEPAGE *bp, long fn, short nargs, \
		short mode, long flags, char *cmd, char *tail, char *env, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	short oldout = 0, newout = -1, olderr = 0;
	long r;

	if (nargs < 5) return -EINVAL;
	if (nargs >= 6) proc = p;
	if ((nargs < 6) || !proc) proc = get_contrl(bp);

	if (flags & 4)
		_signal(proc, SIGCHLD, sig_child);

	if (flags & 3)
	{
		newout = _open(proc, "u:/dev/null", O_WRONLY);
		if (newout >= 0)
		{
			if (flags & 1)
			{
				oldout = _dup(proc, 1);
				_force(proc, 1, newout);
			}
			if (flags & 2)
			{
				olderr = _dup(proc, 2);
				_force(proc, 2, newout);
			}
		}
	}

	r = _pexec(proc, mode, cmd, tail, env);

	if ((flags & 3) && (newout >= 0))
	{
		if (flags & 1)
			_force(proc, 1, oldout);
		if (flags & 2)
			_force(proc, 2, olderr);
		_close(proc, newout);
	}

	return r;
}

long
thread_fork(BASEPAGE *bp, long fn, short nargs, \
		void *startup, void *address, char *proctitle, long stacksize, long opt, PROC_ARRAY *p)
{
	PROC_ARRAY *proc = 0;
	BASEPAGE *new;
	long execmode, mode = 0, flags, size, oldsig = 0, pid;

	if (nargs < 3) return -EINVAL;
	if (nargs >= 5) mode = opt;
	if (nargs >= 6) proc = p;
	if ((nargs < 6) || !proc) proc = get_contrl(bp);

	if (fn == 13)
		execmode = 104;		/* just go, sharing mode */
	else
		execmode = 204;		/* overlay, then go */

	flags = getprgflags(proc);

	sema_request(sema_fork);

	new = (BASEPAGE *)_pexec(proc, 7L, (void *)flags, "", 0L);
	if ((long)new < 0)
		new = (BASEPAGE *)_pexec(proc, 5L, 0L, "", 0L); 
	if ((long)new <= 0)
	{
		sema_release(sema_fork);
		if (!(long)new)
			return -ENOMEM;
		return (long)new;
	}
	if (nargs >= 4)
		size = stacksize;
	else
		size = 0x00001f00L;
	size += 0x00000100L;
	_shrink(proc, new, size);

	sema_release(sema_fork);

	new->p_tbase = startup;
	new->p_dbase = address;

	if (mode & 1)
		oldsig = _signal(proc, SIGCHLD, sig_child);

	pid = _pexec(proc, execmode, proctitle, (char *)new, 0L);

	_free(proc, (long)new->p_env);
	_free(proc, (long)new);

	if (oldsig && (pid < 0))
		_signal(proc, SIGCHLD, (void *)oldsig);

	return pid;
}

/* EOF */
