/* Main module */

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

# include <mintbind.h>
# include <fcntl.h>
# include <mint/dcntl.h>
# include <errno.h>
# include <string.h>

# include "gemma.h"
# include "dosproto.h"
# include "misc.h"
# include "rsrc.h"

long gemma_init(void);
void gemma_exit(void);
long gemma_open(BASEPAGE *bp);
void gemma_close(BASEPAGE *bp);

/* Global variables */

PROC_ARRAY *pidtable[MAX_PID+1];
const long sema_fork = (const long)gemma_init;
const long sema_users = (const long)get_users;

# ifdef DEBUG
void
debug_print(const char *function, const char *string)
{
	(void) Cconws(function);
	(void) Cconws("(): ");
	(void) Cconws(string);
	(void) Cconws("\r\n");
}
# endif

/* Utility routines */

# if 0
static long
get_page_size(void)
{
	short drv;
	char d, cwd[512];
	long r, meminfo[4];

	drv = Dgetdrv();
	d = 'U' - 'A';
	Dsetdrv((short)d);
	r = Dgetcwd(cwd, 0, sizeof(cwd));
	if (r < 0)
	{
		Dsetdrv(drv);
		return sflags.pagesize;
	}
	if (!cwd[0])
	{
		cwd[0] = '\\';
		cwd[1] = 0;
	}
	r = Dsetpath("u:\\proc");
	if (r < 0)
	{
		Dsetdrv(drv);
		return sflags.pagesize;
	}
	r = Dfree((long *)meminfo, 0);
	Dsetpath(cwd);
	Dsetdrv(drv);
	if (r < 0)
		return sflags.pagesize;
	if (meminfo[3] < sflags.minpagesize)
		return sflags.pagesize;

	return meminfo[3];
}
# endif

/* Internal utilities */

OBJECT *
obj2addr(PROC_ARRAY *proc, short type, ulong obj)
{
	if (obj > 65535UL)
		return (OBJECT *)obj;

	return (OBJECT *)rsrc_xgaddr(proc->base, RSRC_XGADDR, 3, type, (short)obj, proc);
}

PROC_ARRAY *
get_contrl(BASEPAGE *bp)
{
	return pidtable[Pgetpid()];
}

static void
write_pidtable(short pid, PROC_ARRAY *value)
{
	sema_request(sema_users);
	pidtable[pid] = value;
	sema_release(sema_users);
}

/* System routines */

long
gemma_init(void)
{
	long r;

# if 0
	sflags.pagesize = get_page_size();
# endif
	r = sema_create(sema_users);
	if (r >= 0)
		sema_release(sema_users);
	r = sema_create(sema_fork);
	if (r < 0)
		return 0;
	return sema_release(sema_fork);
}

void
gemma_exit(void)
{
	long r;

	r = sema_request(sema_users);
	if (r >= 0)
		sema_destroy(sema_users);
	r = sema_request(sema_fork);
	if (r < 0)
		return;
	sema_destroy(sema_fork);
}

/* Process intialization and closing */

long
gemma_open(BASEPAGE *bp)
{
	PROC_ARRAY *proc;
	long pid = Pgetpid();
	short drv;

	if (pid > MAX_PID)
	{
		(void) Cconws("gemma.slb: cannot service so many processes!!\r\n");
		return -EPROCLIM;
	}

	proc = (PROC_ARRAY *)_alloc(sizeof(PROC_ARRAY));
	if ((long)proc < 0)
		return (long)proc;

	write_pidtable(pid, proc);
	bzero(proc, sizeof(PROC_ARRAY));

	proc->gem.aesparams[0] = (long)&proc->gem.control[0];
	proc->gem.aesparams[1] = (long)&proc->gem.global[0];
	proc->gem.aesparams[2] = (long)&proc->gem.int_in[0];
	proc->gem.aesparams[3] = (long)&proc->gem.int_out[0];
	proc->gem.aesparams[4] = (long)&proc->gem.addr_in[0];
	proc->gem.aesparams[5] = (long)&proc->gem.addr_out[0];

	proc->gem.vdiparams[0] = (long)&proc->gem.contrl[0];
	proc->gem.vdiparams[1] = (long)&proc->gem.intin[0];
	proc->gem.vdiparams[2] = (long)&proc->gem.ptsin[0];
	proc->gem.vdiparams[3] = (long)&proc->gem.intout[0];
	proc->gem.vdiparams[4] = (long)&proc->gem.ptsout[0];

	proc->base = bp;
	drv = Dgetdrv();
	proc->bvset = Dsetdrv(drv);

	return 0;
}

void
gemma_close(BASEPAGE *bp)
{
	long pid = Pgetpid();
	PROC_ARRAY *proc;

	proc = pidtable[pid];
	if (!proc)
		return;		/* huuh? */

	write_pidtable(pid, 0);
	Mfree((long)proc);
}

/* EOF */
