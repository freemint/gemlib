/* Main module */

# include <fcntl.h>
# include <mintbind.h>
# include <mint/dcntl.h>
# include <errno.h>
# include <string.h>

# include "gemma.h"
# include "user.h"

long gemma_init(void);

/* Global variables */

PROC_ARRAY *pidtable[MAX_PID+1];
long users;			/* number of processes using the lib */
short whitebak;

static const char procpath[] = "u:\\proc";
const long sema_fork = (const long)gemma_init;

# ifdef DEBUG
void
debug_print(char *string)
{
	char msg[128], c;
	short x, y = 0;

	for (x = 0; x < 128; x++)
	{
		c = string[x];
		if (c == '\n')
		{
			msg[y] = '\r';
			y++;
		}
		msg[y++] = c;
		if (!c)
			break;
	}
	Cconws(msg);
}
# endif

/* Utility routines */

char *
getenv(BASEPAGE *bp, const char *var)
{
	char *env = (char *)bp->p_env;
	long len = strlen(var);

	do {
		if (strncmp(env, var, len) == 0)
		{
			env += len;

			DEBUGMSG("getenv: -> ");
			DEBUGMSG(env);
			DEBUGMSG("\n");

			return env;
		}
		while(*env++);
	} while(*env);

	return 0;
}

static inline long
get_page_size(void)
{
	short drv;
	char d, cwd[512];
	long r, meminfo[4];

	drv = Dgetdrv();
	d = procpath[0];
	d &= 0x5f;
	d -= 'A';
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
	r = Dsetpath(procpath);
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

long
__malloc(long size, short mode)
{
	long r;

	sema_request(sema_fork);
	r = Mxalloc(size, mode);
	if (r < 0)
		r = Malloc(size);	/* No Mxalloc()? Incredible... */
	sema_release(sema_fork);
	if (!r)
		r = -ENOMEM;
	return r;
}

void
_mfree(long adr)
{
	Mfree(adr);
}

static long
_getpid(BASEPAGE *bp)
{
	PROC_ARRAY *proc;
	long p = Pgetpid();

	if (p < 0)
	{
		for (p = 0; p <= MAX_PID; p++)
		{
			proc = pidtable[p];
			if (proc->base == bp)
				return p;
		}
	}
	return p;
}

/* System routines */

long
gemma_init(void)
{
	long r;

	r = sema_create(sema_fork);
	sflags.pagesize = get_page_size();
	if (r < 0)
		return 0;
	return sema_release(sema_fork);
}

void
gemma_exit(void)
{
	long r;

	r = sema_request(sema_fork);
	if (r < 0)
		return;
	sema_destroy(sema_fork);
	return;
}

/* Process intialization and closing */

long
gemma_open(BASEPAGE *bp)
{
	PROC_ARRAY *proc;
	long pid = Pgetpid();

	sema_request(sema_fork);

	if (pid < 0)
	{
		for (pid = 1; pid <= MAX_PID; pid++)
		{
			if (!pidtable[pid])
				goto found;
		}
		pid = MAX_PID + 1;
	}
found:
	sema_release(sema_fork);

	if (pid > MAX_PID)
	{
		Cconws("gemma.slb: cannot service so many processes!!\r\n");
		return -EPROCLIM;
	}

	proc = (PROC_ARRAY *)_malloc(sizeof(PROC_ARRAY));
	if ((long)proc < 0)
		return (long)proc;
	pidtable[pid] = proc;
	bzero(proc, sizeof(PROC_ARRAY));

	proc->gem.aesparams[0] = (long)proc->gem.control;
	proc->gem.aesparams[1] = (long)proc->gem.global;
	proc->gem.aesparams[2] = (long)proc->gem.int_in;
	proc->gem.aesparams[3] = (long)proc->gem.int_out;
	proc->gem.aesparams[4] = (long)proc->gem.addr_in;
	proc->gem.aesparams[5] = (long)proc->gem.addr_out;

	proc->gem.vdiparams[0] = (long)proc->gem.contrl;
	proc->gem.vdiparams[1] = (long)proc->gem.intin;
	proc->gem.vdiparams[2] = (long)proc->gem.ptsin;
	proc->gem.vdiparams[3] = (long)proc->gem.intout;
	proc->gem.vdiparams[4] = (long)proc->gem.ptsout;

	proc->base = bp;

	users++;

	return 0;		/* uff */
}

void
gemma_close(BASEPAGE *bp)
{
	long pid = _getpid(bp);
	PROC_ARRAY *proc;

	users--;
	proc = pidtable[pid];
	if ((long)proc == 0)
		return;		/* huuh? */
	pidtable[pid] = 0;
	_mfree((long)proc);
}

/* Internal utilities */

OBJECT *
obj2addr(PROC_ARRAY *proc, short type, ulong obj)
{
	if (obj > 65536UL)
		return (OBJECT *)obj;

	return (OBJECT *)rsrc_xgaddr(proc->base, 0L, 3, type, (short)obj, proc);
}

PROC_ARRAY *
get_contrl(BASEPAGE *bp)
{
	return pidtable[_getpid(bp)];
}

/* EOF */
