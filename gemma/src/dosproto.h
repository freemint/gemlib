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

#undef SLB_NWORDS
#define SLB_NWORDS(_nargs) ((((long)(_nargs) * 2 + 1l) << 16) | (long)(_nargs))
#undef SLB_NARGS
#define SLB_NARGS(_nargs) SLB_NWORDS(_nargs)

#ifndef _CDECL
#  define _CDECL
#endif

const char *dos_serror(PROC_ARRAY *proc, long error);
long dos_fsize(PROC_ARRAY *proc, const char *name);
long dos_fsearch(PROC_ARRAY *proc, const char *name, char *fullname, const char *envvar);
const char *dos_getenv(PROC_ARRAY *proc, const char *var);
long dos_floadbuf(PROC_ARRAY *proc, const char *name, char *buf, long len, short *mode);

long dos_pexec(PROC_ARRAY *proc, long mode, const char *cmd, const char *tail, const char *env);

#if _USE_KERNEL32

long dos_wait3(PROC_ARRAY *proc, short flag, long *rus);
long dos_signal(PROC_ARRAY *proc, short sig, void *hnd);
long dos_kill(PROC_ARRAY *proc, short pid, short sig);
long dos_fcntl(PROC_ARRAY *proc, short file, void *arg, short cmd);
long dos_pdomain(PROC_ARRAY *proc, long dom);
long dos_dopendir(PROC_ARRAY *proc, const char *name, short flag);
long dos_dreaddir(PROC_ARRAY *proc, long size, long handle, void *buf);
long dos_drewinddir(PROC_ARRAY *proc, long handle);
long dos_dclosedir(PROC_ARRAY *proc, long handle);
void dos_yield(PROC_ARRAY *proc);
long dos_fopen(PROC_ARRAY *proc, const char *name, short mode);
void dos_fclose(PROC_ARRAY *proc, long fd);
long dos_fread(PROC_ARRAY *proc, long fd, long len, void *buf);
long dos_fwrite(PROC_ARRAY *proc, long fd, long len, const void *buf);
long dos_fdelete(PROC_ARRAY *proc, const char *filespec);
long dos_fdup(PROC_ARRAY *proc, short file);
void dos_fforce(PROC_ARRAY *proc, short f1, short f2);
void dos_mshrink(PROC_ARRAY *proc, void *base, long newsize);
void dos_mfree(PROC_ARRAY *proc, long addr);
long dos_pgetppid(PROC_ARRAY *proc);
long dos_pgetpid(PROC_ARRAY *proc);

#else

#include <mintbind.h>

#define dos_wait3(proc, flag, rus) Pwait3(flag, rus)
#define dos_signal(proc, sig, hnd) Psignal(sig, hnd)
#define dos_kill(proc, pid, sig) Pkill(pid, sig)
#define dos_fcntl(proc, file, arg, cmd) Fcntl(file, arg, cmd)
#define dos_pdomain(proc, dom) Pdomain(dom)
#define dos_dopendir(proc, name, flag) Dopendir(name, flag)
#define dos_dreaddir(proc, size, handle, buf) Dreaddir(size, handle, buf)
#define dos_drewinddir(proc, handle) Drewinddir(handle)
#define dos_dclosedir(proc, handle) Dclosedir(handle)
#define dos_yield(proc) Syield()
#define dos_fopen(proc, name, mode) Fopen(name, mode)
#define dos_fclose(proc, fd) Fclose(fd)
#define dos_fread(proc, fd, len, buf) Fread(fd, len, buf)
#define dos_fwrite(proc, fd, len, buf) Fwrite(fd, len, buf)
#define dos_fdelete(proc, filespec) Fdelete(filespec)
#define dos_fdup(proc, file) Fdup(file)
#define dos_fforce(proc, f1, f2) Fforce(f1, f2)
#define dos_mshrink(proc, base, newsize) Mshrink(base, newsize)
#define dos_mfree(proc, addr) Mfree(addr)
#define dos_pgetppid(proc) Pgetppid()
#define dos_pgetpid(proc) Pgetpid()

#endif

long _sgetpid(void);
long _sgeteuid(void);
long _semaphore(short mode, long sema, long time);

void _conws(const char *str);

long _alloc(long size);
long _rdalloc(long size);

long _getdrv(void);
long _setpath(const char *p);
long _getcwd(void *p, short drv, short len);

/* EOF */
