/* Prototypes for dosproto.c
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

# define sema_create(s) _semaphore(0, s, 0L)
# define sema_destroy(s) _semaphore(1, s, 0L)
# define sema_request(s) _semaphore(2, s, -1L)
# define sema_release(s) _semaphore(3, s, 0L)

long _getexc(long vec);
short _kbshift(long wh);
short _getrez(void);

#undef SLB_NWORDS
#define SLB_NWORDS(_nargs) ((((long)(_nargs) * 2 + 1l) << 16) | (long)(_nargs))
#undef SLB_NARGS
#define SLB_NARGS(_nargs) SLB_NWORDS(_nargs)

#ifndef _CDECL
#  define _CDECL
#endif

INLINE
long _floadbuf(PROC_ARRAY *proc, const char *name, char *buf, long len, short *mode)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, char *, long, short *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, char *, long, short *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x020bL, SLB_NARGS(4), name, buf, len, mode);
}

INLINE
long _pexec(PROC_ARRAY *proc, long mode, char *cmd, char *tail, char *env)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, char *, char *, char *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, char *, char *, char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 75L, SLB_NARGS(4), mode, cmd, tail, env);
}

INLINE
long _wait3(PROC_ARRAY *proc, short flag, long *rus)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x011cL, SLB_NARGS(2), flag, rus);
}

INLINE
long _signal(PROC_ARRAY *proc, short sig, void *hnd)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0112L, SLB_NARGS(2), sig, hnd);
}

INLINE
long _kill(PROC_ARRAY *proc, short pid, short sig)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0111L, SLB_NARGS(2), pid, sig);
}

INLINE
char *getenv(PROC_ARRAY *proc, const char *var)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *))proc->kern.exec;
	return (char *)(*exec)(proc->kern.handle, 0x0208L, SLB_NARGS(1), var);
}

INLINE
long _cntl(PROC_ARRAY *proc, short file, void *arg, short cmd)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, void *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long, void *, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0104, SLB_NARGS(3), file, arg, cmd);
}

INLINE
long _domain(PROC_ARRAY *proc, long dom)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0119L, SLB_NARGS(1), dom);
}

INLINE
long _opendir(PROC_ARRAY *proc, const char *name, short flag)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0128L, SLB_NARGS(2), name, flag);
}

INLINE
long _readdir(PROC_ARRAY *proc, long size, long handle, void *buf)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long, void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long, void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0129L, SLB_NARGS(3), size, handle, buf);
}

INLINE
long _rewinddir(PROC_ARRAY *proc, long handle)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x012aL, SLB_NARGS(1), handle);
}

INLINE
long _closedir(PROC_ARRAY *proc, long handle)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x012bL, SLB_NARGS(1), handle);
}

INLINE
void _yield(PROC_ARRAY *proc)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x00ffL, SLB_NARGS(0));
}

INLINE
long _size(PROC_ARRAY *proc, const char *name)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0201L, SLB_NARGS(1), name);
}

INLINE
long _open(PROC_ARRAY *proc, const char *name, short mode)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x003dL, SLB_NARGS(2), name, mode);
}

INLINE
void _close(PROC_ARRAY *proc, long fd)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x003eL, SLB_NARGS(1), fd);
}

INLINE
long _read(PROC_ARRAY *proc, long fd, long len, void *buf)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long, void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long, void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x003fL, SLB_NARGS(3), fd, len, buf);
}

INLINE
long _write(PROC_ARRAY *proc, long fd, long len, const void *buf)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long, const void *) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long, const void *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0040L, SLB_NARGS(3), fd, len, buf);
}

INLINE
long _delete(PROC_ARRAY *proc, const char *filespec)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, const char *) = (long _CDECL (*)(SLB_HANDLE, long, long, const char *))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0041L, SLB_NARGS(1), filespec);
}

INLINE
long _dup(PROC_ARRAY *proc, short file)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x0045L, SLB_NARGS(1), file);
}

INLINE
void _force(PROC_ARRAY *proc, short f1, short f2)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x0046L, SLB_NARGS(2), f1, f2);
}

INLINE
void _shrink(PROC_ARRAY *proc, void *base, long newsize)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, void *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, void *, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x004aL, SLB_NARGS(2), base, newsize);
}

INLINE
void _free(PROC_ARRAY *proc, long addr)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long, long))proc->kern.exec;
	(*exec)(proc->kern.handle, 0x0049L, SLB_NARGS(1), addr);
}

INLINE
long _getppid(PROC_ARRAY *proc)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x010cL, SLB_NARGS(0));
}

# if 0
INLINE
long _getpid(PROC_ARRAY *proc)
{
	long _CDECL (*exec)(SLB_HANDLE, long, long) = (long _CDECL (*)(SLB_HANDLE, long, long))proc->kern.exec;
	return (*exec)(proc->kern.handle, 0x010bL, SLB_NARGS(0));
}
# endif

long _sgetpid(void);
long _sgeteuid(void);
long _semaphore(short mode, long sema, long time);

void _conws(char *str);

long _alloc(long size);
long _rdalloc(long size);

long _getdrv(void);
long _setpath(const char *p);
long _getcwd(void *p, short drv, short len);

#undef SLB_NWORDS
#undef SLB_NARGS

/* EOF */
