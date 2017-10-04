/* GEMDOS function gateway
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

# include <errno.h>
# include <string.h>
# include <mintbind.h>
# include <limits.h>

# include "gemma.h"
# include "dosproto.h"

/* These below are only used in appl_getinfo() emulation code
 */

/* GEMDOS function calls
 */

void
_conws(const char *string)
{
	short x = 0;

	while(string[x])
	{
		if (string[x] == '\n')
			(void) Cconws("\r\n");
		else
			Cconout(string[x]);
		x++;
	}
}

static void
u2d(const char *in, char *out)
{
	if ((in[1] != ':') && ((in[0] == '\\') || (in[0] == '/')))
	{
		strcpy(out, "u:");
		strcat(out, in);
	}
	else
		strcpy(out, in);
}

static long
__alloc(long size, short mode)
{
	long r;

	sema_request(sema_fork);
	r = (long)Mxalloc(size, mode);
	if (r < 0)
		r = (long)Malloc(size);	/* No Mxalloc()? Incredible... */
	sema_release(sema_fork);
	if (!r)
		r = -ENOMEM;
	return r;
}

long
_alloc(long size)	/* alloc `size' bytes of private memory */
{
	return __alloc(size, 0x0013);
}

long
_rdalloc(long size)	/* alloc `size' bytes of globally readable memory */
{
	return __alloc(size, 0x0043);
}

long
_getdrv(void)
{
	return Dgetdrv();
}

long
_setpath(const char *p)
{
	char temp[PATH_MAX];

	u2d(p, temp);
	return Dsetpath(temp);
}

long
_getcwd(void *p, short drv, short len)
{
	long r;

	r = Dgetcwd(p, drv, len);
	if (r < 0)
		r = Dgetpath(p, drv);

	return r;
}

long
_semaphore(short mode, long sema, long time)
{
	return Psemaphore(mode, sema, time);
}

long
_sgeteuid(void)
{
	long r = Pgeteuid();
	if (r == -ENOSYS)
		r = Pgetuid();
	if (r == -ENOSYS)
		r = 0;
	return r;
}

const char *dos_serror(PROC_ARRAY *proc, long error)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (const char *)(*exec)(proc->kern.handle, 0x0200, SLB_NARGS(1), error);
}

long dos_fsize(PROC_ARRAY *proc, const char *name)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0201L, SLB_NARGS(1), name);
}

long dos_fsearch(PROC_ARRAY *proc, const char *name, char *fullname, const char *envvar)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, char *, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, char *, const char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x203, SLB_NARGS(3), name, fullname, envvar);
}

const char *dos_getenv(PROC_ARRAY *proc, const char *var)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *))proc->kern.exec;
	return (char *)(*exec)(proc->kern.handle, 0x0208L, SLB_NARGS(1), var);
}

long dos_floadbuf(PROC_ARRAY *proc, const char *name, char *buf, long len, short *mode)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, char *, long, short *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, char *, long, short *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x020bL, SLB_NARGS(4), name, buf, len, mode);
}

long dos_pexec(PROC_ARRAY *proc, long mode, const char *cmd, const char *tail, const char *env)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, const char *, const char *, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, const char *, const char *, const char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 75L, SLB_NARGS(4), mode, cmd, tail, env);
}

long dos_wait3(PROC_ARRAY *proc, short flag, long *rus)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x011cL, SLB_NARGS(2), flag, rus);
}

long dos_signal(PROC_ARRAY *proc, short sig, void *hnd)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0112L, SLB_NARGS(2), sig, hnd);
}

long dos_kill(PROC_ARRAY *proc, short pid, short sig)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0111L, SLB_NARGS(2), pid, sig);
}

long dos_fcntl(PROC_ARRAY *proc, short file, void *arg, short cmd)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, void *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long, void *, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0104, SLB_NARGS(3), file, arg, cmd);
}

long dos_pdomain(PROC_ARRAY *proc, long dom)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0119L, SLB_NARGS(1), dom);
}

long dos_dopendir(PROC_ARRAY *proc, const char *name, short flag)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0128L, SLB_NARGS(2), name, flag);
}

long dos_dreaddir(PROC_ARRAY *proc, long size, long handle, void *buf)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long, void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long, void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0129L, SLB_NARGS(3), size, handle, buf);
}

#if 0
long dos_drewinddir(PROC_ARRAY *proc, long handle)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x012aL, SLB_NARGS(1), handle);
}
#endif

long dos_dclosedir(PROC_ARRAY *proc, long handle)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x012bL, SLB_NARGS(1), handle);
}

void dos_yield(PROC_ARRAY *proc)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x00ffL, SLB_NARGS(0));
}

long dos_fopen(PROC_ARRAY *proc, const char *name, short mode)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x003dL, SLB_NARGS(2), name, mode);
}

void dos_fclose(PROC_ARRAY *proc, long fd)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x003eL, SLB_NARGS(1), fd);
}

long dos_fread(PROC_ARRAY *proc, long fd, long len, void *buf)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long, void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long, void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x003fL, SLB_NARGS(3), fd, len, buf);
}

long dos_fwrite(PROC_ARRAY *proc, long fd, long len, const void *buf)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long, const void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long, const void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0040L, SLB_NARGS(3), fd, len, buf);
}

long dos_fdelete(PROC_ARRAY *proc, const char *filespec)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0041L, SLB_NARGS(1), filespec);
}

long dos_fdup(PROC_ARRAY *proc, short file)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0045L, SLB_NARGS(1), file);
}

void dos_fforce(PROC_ARRAY *proc, short f1, short f2)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x0046L, SLB_NARGS(2), f1, f2);
}

void dos_mshrink(PROC_ARRAY *proc, void *base, long newsize)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, void *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, void *, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x004aL, SLB_NARGS(2), base, newsize);
}

void dos_mfree(PROC_ARRAY *proc, long addr)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x0049L, SLB_NARGS(1), addr);
}

long dos_pgetppid(PROC_ARRAY *proc)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x010cL, SLB_NARGS(0));
}

# if 0
long dos_pgetpid(PROC_ARRAY *proc)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x010bL, SLB_NARGS(0));
}
# endif

/* EOF */
