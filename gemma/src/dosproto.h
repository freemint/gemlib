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

INLINE
long _floadbuf(PROC_ARRAY *proc, const char *name, char *buf, long len, short *mode)
{
	return (proc->kern.exec)(proc->kern.handle, 0x020bL, (short)4, name, buf, len, mode);
}

INLINE
long _pexec(PROC_ARRAY *proc, long mode, char *cmd, char *tail, char *env)
{
	return (proc->kern.exec)(proc->kern.handle, 75L, (short)4, (long)mode, (long)cmd, (long)tail, (long)env);
}

INLINE
long _wait3(PROC_ARRAY *proc, short flag, long *rus)
{
	return (proc->kern.exec)(proc->kern.handle, 0x011cL, (short)flag, (long)rus);
}

INLINE
long _signal(PROC_ARRAY *proc, short sig, void *hnd)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0112L, (short)sig, (long)hnd);
}

INLINE
long _kill(PROC_ARRAY *proc, short pid, short sig)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0111L, (short)pid, (short)sig);
}

INLINE
char *getenv(PROC_ARRAY *proc, const char *var)
{
	return (char *)(proc->kern.exec)(proc->kern.handle, 0x0208L, (short)1, (long)var);
}

INLINE
long _cntl(PROC_ARRAY *proc, short file, void *arg, short cmd)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0104, (short)3, (short)file, (long)arg, (short)cmd);
}

INLINE
long _domain(PROC_ARRAY *proc, long dom)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0119L, (short)1, (long)dom);
}

INLINE
long _opendir(PROC_ARRAY *proc, const char *name, short flag)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0128L, (short)2, (long)name, (short)flag);
}

INLINE
long _readdir(PROC_ARRAY *proc, long size, long handle, void *buf)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0129L, (short)3, (long)size, (long) handle, (long)buf);
}

INLINE
long _rewinddir(PROC_ARRAY *proc, long handle)
{
	return (proc->kern.exec)(proc->kern.handle, 0x012aL, (short)1, (long) handle);
}

INLINE
long _closedir(PROC_ARRAY *proc, long handle)
{
	return (proc->kern.exec)(proc->kern.handle, 0x012bL, (short)1, (long) handle);
}

INLINE
void _yield(PROC_ARRAY *proc)
{
	(proc->kern.exec)(proc->kern.handle, 0x00ffL, (short)0);
}

INLINE
long _size(PROC_ARRAY *proc, char *name)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0201L, (short)1, name);
}

INLINE
long _open(PROC_ARRAY *proc, const char *name, short mode)
{
	return (proc->kern.exec)(proc->kern.handle, 0x003dL, (short)2, name, mode);
}

INLINE
void _close(PROC_ARRAY *proc, long fd)
{
	(proc->kern.exec)(proc->kern.handle, 0x003eL, (short)1, (short)fd);
}

INLINE
long _read(PROC_ARRAY *proc, long fd, long len, void *buf)
{
	return (proc->kern.exec)(proc->kern.handle, 0x003fL, (short)3, (short)fd, len, buf);
}

INLINE
long _write(PROC_ARRAY *proc, long fd, long len, void *buf)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0040L, (short)3, (short)fd, len, buf);
}

INLINE
long _delete(PROC_ARRAY *proc, const char *filespec)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0041L, (short)1, (long)filespec);
}

INLINE
long _dup(PROC_ARRAY *proc, short file)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0045L, (short)1, (short)file);
}

INLINE
void _force(PROC_ARRAY *proc, short f1, short f2)
{
	(proc->kern.exec)(proc->kern.handle, 0x0046L, (short)2, (short)f1, (short)f2);
}

INLINE
void _shrink(PROC_ARRAY *proc, void *base, long newsize)
{
	(proc->kern.exec)(proc->kern.handle, 0x004aL, (short)2, (long)base, (long)newsize);
}

INLINE
void _free(PROC_ARRAY *proc, long addr)
{
	(proc->kern.exec)(proc->kern.handle, 0x0049L, (short)1, (long)addr);
}

INLINE
long _getppid(PROC_ARRAY *proc)
{
	return (proc->kern.exec)(proc->kern.handle, 0x010cL, (short)0);
}

# if 0
INLINE
long _getpid(PROC_ARRAY *proc)
{
	return (proc->kern.exec)(proc->kern.handle, 0x010bL, (short)0);
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

/* EOF */
