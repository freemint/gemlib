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
# include <sys/stat.h>

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

#if _USE_KERNEL32
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

#else

#include "../kernel32/errlist.h"

#ifndef __XATTR
#define __XATTR
typedef struct xattr
{
	unsigned short st_mode;
	long           st_ino;	/* must be 32 bits */
	unsigned short st_dev;	/* must be 16 bits */
	unsigned short st_rdev;	/* not supported by the kernel */
	unsigned short st_nlink;
	unsigned short st_uid;	/* must be 16 bits */
	unsigned short st_gid;	/* must be 16 bits */
	long           st_size;
	long           st_blksize;
	long           st_blocks;
	unsigned long  st_mtime;
	unsigned long  st_atime;
	unsigned long  st_ctime;
	short          st_attr;
	short res1;		/* reserved for future kernel use */
	long res2[2];
} XATTR;
#endif


const char *dos_serror(PROC_ARRAY *proc, long error)
{
	short i;
	
	UNUSED(proc);
	if (error != 0)
	{
		for (i = 0; errorlist[i].code != 0; i++)
		{
			if (errorlist[i].code == error)
				return errorlist[i].text;
		}
		return "Unknown error";
	}
	return "No errors";
}

static char *bp_getenv(BASEPAGE *bp, const char *var)
{
	char *env = bp->p_env;
	size_t len = strlen(var);

	do {
		if (strncmp(env, var, len) == 0)
			return env + len;
		while (*env++ != '\0')
		{
			/* nothing */
		}
	} while (*env != '\0');
	return NULL;
}


long dos_fsize(PROC_ARRAY *proc, const char *name)
{
	struct stat st;
	struct xattr xattr;
	_DTA *olddta;
	_DTA dta;
	long ret;

	UNUSED(proc);
	if (Fstat64(0, name, &st) == 0)
		return st.st_size;
	if (Fxattr(0, name, &xattr) == 0)
		return xattr.st_size;
	olddta = Fgetdta();
	Fsetdta(&dta);
	ret = Fsfirst(name, 0);
	Fsetdta(olddta);
	if (ret == 0)
		return dta.dta_size;
	return ret;
}


long dos_fsearch(PROC_ARRAY *proc, const char *name, char *fullname, const char *pathvar)
{
	const char *path;
	char *end;
	
	path = dos_getenv(proc, pathvar == NULL ? "PATH=" : pathvar);
	if (path == NULL)
		return -ESRCH;
	while (*path != '\0')
	{
		end = fullname;
		while (*path != '\0' && *path != ',' && *path != ';')
			*end++ = *path++;
		*end = '\0';
		if (*path != '\0')
			path++;
		strcat(fullname, "/");
		strcat(fullname, name);
		if (dos_fsize(proc, fullname) >= 0)
			return 0;
	}
	return -ESRCH;
}

const char *dos_getenv(PROC_ARRAY *proc, const char *var)
{
	return bp_getenv(proc->base, var);
}


/*
 * Simplified version of dos_pexec.
 * Does not handle ARGV argument passing, or hashbang scripts
 */
long dos_pexec(PROC_ARRAY *proc, long mode, const char *ptr1, const char *ptr2, const char *ptr3)
{
	short mkname = 0;
	char *name;
	char namebuf[PATH_MAX];
	char pathbuf[PATH_MAX];
	char tail[128];
	
	size_t i, len;
	
	if (mode != 5 && mode != 7)
	{
		if (mode < 5)
		{
			if (mode != 0 && mode != 3)
				goto do_exec; /* mode 4: just go */
		} else
		{
			if (mode != 100)
			{
				if (mode < 100)
				{
					if (mode != 7)
						goto do_exec; /* mode 6: just go */
				}
				if (mode != 200)
					goto do_exec;
			}
		}
		mkname = 1;
	}

	if (mkname)
	{
		strncpy(namebuf, ptr1, sizeof(namebuf));
		name = namebuf;
		for (i = 0; i < sizeof(namebuf); i++)
		{
			if (name[i] == '\\')
				name[i] = '/';
			if (name[i] == '\0')
				break;
		}
		
		ptr1 = name;
		if (strchr(name, '/') == NULL)
		{
			if (dos_fsize(proc, name) < 0)
			{
				if (dos_fsearch(proc, name, pathbuf, NULL) == 0)
					ptr1 = pathbuf;
			}
		}
	}

	if (ptr2 && *ptr2)
	{
		len = strlen(ptr2);
		if (len > 126)
			return -EBADARG;
		strncpy(tail + 1, ptr2, sizeof(tail) - 1);
		tail[0] = (char)len;
	} else
	{
		tail[0] = tail[1] = '\0';
	}
	ptr2 = tail;
	
do_exec:
	return Pexec(mode, ptr1, ptr2, ptr3);
}


long dos_floadbuf(PROC_ARRAY *proc, const char *fname, char *buf, long size, short *mode)
{
	long fsize;
	struct xattr xattr;
	long ret;
	long handle;

	fsize = dos_fsize(proc, fname);
#if 0
	if (fsize < 0)
		return fsize;
#endif
	if (fsize > size)
		return -ESRCH;
	if (Fxattr(0, fname, &xattr) == 0)
	{
		*mode = xattr.st_mode;
	}
	if ((ret = Fopen(fname, FO_READ)) >= 0)
	{
		handle = ret;
		ret = Fread(handle, fsize, buf);
		Fclose(handle);
		if (ret >= 0 && ret != fsize)
			ret = -EREAD;
	}
	if (ret < 0)
		return ret;
	return 0;
}

#endif /* _USE_KERNEL32 */
