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

static inline
long _domain(PROC_ARRAY *proc, long dom)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0119L, (short)1, (long)dom);
}

static inline
void _yield(PROC_ARRAY *proc)
{
	(proc->kern.exec)(proc->kern.handle, 0x00ffL, (short)0);
}

static inline
long _size(PROC_ARRAY *proc, char *name)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0201L, (short)1, name);
}

static inline
long _open(PROC_ARRAY *proc, const char *name, short mode)
{
	return (proc->kern.exec)(proc->kern.handle, 0x003dL, (short)2, name, mode);
}

static inline
void _close(PROC_ARRAY *proc, long fd)
{
	(proc->kern.exec)(proc->kern.handle, 0x003eL, (short)1, (short)fd);
}

static inline
long _read(PROC_ARRAY *proc, long fd, long len, void *buf)
{
	return (proc->kern.exec)(proc->kern.handle, 0x003fL, (short)3, (short)fd, len, buf);
}

static inline
long _write(PROC_ARRAY *proc, long fd, long len, void *buf)
{
	return (proc->kern.exec)(proc->kern.handle, 0x0040L, (short)3, (short)fd, len, buf);
}

long _cntl(short file, void *arg, short cmd);
long _stat(short flag, const char *name, void *out);

long _wait3(short flag, long *rus);

long _kill(long pid, long sig);
long _sgetpid(void);
long _sgetppid(void);
long _sgeteuid(void);
long _semaphore(short mode, long sema, long time);
long _signal(short sig, void *hnd);

void _conws(char *str);
short _dup(short file);
void _force(short f1, short f2);
long _delete(char *filespec);

long _alloc(long size);
long _rdalloc(long size);
void _shrink(void *base, long newsize);
void _free(long adr);

long _getdrv(void);
long _setdrv(long drv);
long _dfree(long *m, short d);
long _getpath(void *p, short drv);
long _setpath(const char *p);
long _getcwd(void *p, short drv, short len);

/* EOF */
