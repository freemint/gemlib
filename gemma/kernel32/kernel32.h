/*
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/>. 
 *
 */

#include <mintbind.h>
#include <mint/basepage.h>
#include <mint/slb.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

#ifdef __MSHORT__
# error "the kernel32.slb must not be compiled with -mshort"
#endif
struct check_not_mshort { unsigned int error_if_negative: sizeof(int) == 4 ? 1 : -1; };

#include "../../gemlib/gem.h"

#include "../config.h"

#ifndef UNUSED
#  define UNUSED(x) ((void)(x))
#endif

#undef NULL
#define NULL ((void *)0)

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


#undef SLB_NWORDS
#define SLB_NWORDS(_nargs) ((((long)(_nargs) * 2 + 1l) << 16) | (long)(_nargs))
#undef SLB_NARGS
#define SLB_NARGS(_nargs) SLB_NWORDS(_nargs)

long kernel32_init(void);
void kernel32_exit(void);
long kernel32_open(BASEPAGE *bp);
void kernel32_close(BASEPAGE *bp);

long dos_pterm0(BASEPAGE *bp, long fn, short nargs);
long dos_pterm(BASEPAGE *bp, long fn, short nargs, long retcode);
long dos_pexec(BASEPAGE *bp, long fn, short nargs, short mode, const char *ptr1, const char *ptr2, const void *ptr3);
long dos_pwait(BASEPAGE *bp, long fn, short nargs);
long dos_pnice(BASEPAGE *bp, long fn, short nargs, short delta);
long dos_pgetpid(BASEPAGE *bp, long fn, short nargs);
long dos_pgetppid(BASEPAGE *bp, long fn, short nargs);
long dos_pgetpgrp(BASEPAGE *bp, long fn, short nargs);
long dos_psetpgrp(BASEPAGE *bp, long fn, short nargs, short pid, short newgrp);
long dos_pgetuid(BASEPAGE *bp, long fn, short nargs);
long dos_psetuid(BASEPAGE *bp, long fn, short nargs, short id);
long dos_pkill(BASEPAGE *bp, long fn, short nargs, short pid, short sig);
long dos_psignal(BASEPAGE *bp, long fn, short nargs, short sig, long handler);
long dos_pvfork(BASEPAGE *bp, long fn, short nargs);
long dos_pgetgid(BASEPAGE *bp, long fn, short nargs);
long dos_psetgid(BASEPAGE *bp, long fn, short nargs, short id);
long dos_psigblock(BASEPAGE *bp, long fn, short nargs, long mask);
long dos_psigsetmask(BASEPAGE *bp, long fn, short nargs, long mask);
long dos_pusrval(BASEPAGE *bp, long fn, short nargs, long val);
long dos_pdomain(BASEPAGE *bp, long fn, short nargs, short dom);
void dos_psigreturn(BASEPAGE *bp, long fn, short nargs);
long dos_pfork(BASEPAGE *bp, long fn, short nargs);
long dos_pwait3(BASEPAGE *bp, long fn, short nargs, short flag, long *rusage);
long dos_prusage(BASEPAGE *bp, long fn, short nargs, long *rusage);
long dos_psetlimit(BASEPAGE *bp, long fn, short nargs, short lim, long val);
void dos_pause(BASEPAGE *bp, long fn, short nargs);
long dos_psigpending(BASEPAGE *bp, long fn, short nargs);
long dos_pmsg(BASEPAGE *bp, long fn, short nargs, short mode, long mbox, void *msg);
long dos_prenice(BASEPAGE *bp, long fn, short nargs, short pid, short delta);
long dos_pumask(BASEPAGE *bp, long fn, short nargs, short mask);
long dos_psemaphore(BASEPAGE *bp, long fn, short nargs, short mode, long id, long timeout);
void dos_psigpause(BASEPAGE *bp, long fn, short nargs, long mask);
long dos_psigaction(BASEPAGE *bp, long fn, short nargs, short sig, struct sigaction *act, struct sigaction *oact);
long dos_pgeteuid(BASEPAGE *bp, long fn, short nargs);
long dos_pgetegid(BASEPAGE *bp, long fn, short nargs);
long dos_pwaitpid(BASEPAGE *bp, long fn, short nargs, short pid, short flag, long *rusage);
long dos_pseteuid(BASEPAGE *bp, long fn, short nargs, short euid);
long dos_psetegid(BASEPAGE *bp, long fn, short nargs, short egid);
long dos_pgetauid(BASEPAGE *bp, long fn, short nargs);
long dos_psetauid(BASEPAGE *bp, long fn, short nargs, short auid);
long dos_pgetgroups(BASEPAGE *bp, long fn, short nargs, short len, unsigned short *gidset);
long dos_psetgroups(BASEPAGE *bp, long fn, short nargs, short len, const unsigned short *gidset);
long dos_psetreuid(BASEPAGE *bp, long fn, short nargs, short ruid, short euid);
long dos_psetregid(BASEPAGE *bp, long fn, short nargs, short rgid, short egid);
long dos_pgetpriority(BASEPAGE *bp, long fn, short nargs, short which, short who);
long dos_psetpriority(BASEPAGE *bp, long fn, short nargs, short which, short who, short pri);

long dos_cconin(BASEPAGE *bp, long fn, short nargs);
void dos_cconout(BASEPAGE *bp, long fn, short nargs, short c);
long dos_cauxin(BASEPAGE *bp, long fn, short nargs);
void dos_cauxout(BASEPAGE *bp, long fn, short nargs, short c);
void dos_cprnout(BASEPAGE *bp, long fn, short nargs, short c);
long dos_crawio(BASEPAGE *bp, long fn, short nargs, short c);
long dos_crawcin(BASEPAGE *bp, long fn, short nargs);
long dos_cnecin(BASEPAGE *bp, long fn, short nargs);
void dos_cconws(BASEPAGE *bp, long fn, short nargs, const char *str);
void dos_cconrs(BASEPAGE *bp, long fn, short nargs, _CCONLINE *buf);
long dos_cconis(BASEPAGE *bp, long fn, short nargs);
long dos_cconos(BASEPAGE *bp, long fn, short nargs);
long dos_cprnos(BASEPAGE *bp, long fn, short nargs);
long dos_cauxis(BASEPAGE *bp, long fn, short nargs);
long dos_cauxos(BASEPAGE *bp, long fn, short nargs);

long dos_dsetdrv(BASEPAGE *bp, long fn, short nargs, short drv);
long dos_dgetdrv(BASEPAGE *bp, long fn, short nargs);
long dos_dfree(BASEPAGE *bp, long fn, short nargs, _DISKINFO *buf, short drv);
long dos_dcreate(BASEPAGE *bp, long fn, short nargs, const char *path);
long dos_ddelete(BASEPAGE *bp, long fn, short nargs, const char *path);
long dos_dsetpath(BASEPAGE *bp, long fn, short nargs, const char *path);
long dos_dgetpath(BASEPAGE *bp, long fn, short nargs, char *path, short drv);
long dos_dpathconf(BASEPAGE *bp, long fn, short nargs, const char *path, short mode);
long dos_dopendir(BASEPAGE *bp, long fn, short nargs, const char *path, short flag);
long dos_dreaddir(BASEPAGE *bp, long fn, short nargs, short len, long dirhandle, char *buf);
long dos_drewinddir(BASEPAGE *bp, long fn, short nargs, long dirhandle);
long dos_dclosedir(BASEPAGE *bp, long fn, short nargs, long dirhandle);
long dos_dcntl(BASEPAGE *bp, long fn, short nargs, short cmd, const char *name, long arg);
long dos_dlock(BASEPAGE *bp, long fn, short nargs, short mode, short drv);
long dos_dgetcwd(BASEPAGE *bp, long fn, short nargs, char *path, short drv, short size);
long dos_dxreaddir(BASEPAGE *bp, long fn, short nargs, short in, long dirhandle, char *buf, XATTR *xattr, long *xr);
long dos_dreadlabel(BASEPAGE *bp, long fn, short nargs, const char *path, char *label, short length);
long dos_dwritelabel(BASEPAGE *bp, long fn, short nargs, const char *path, const char *label);

long dos_srealloc(BASEPAGE *bp, long fn, short nargs, long len);
long dos_slbopen(BASEPAGE *bp, long fn, short nargs, const char *name, const char *path, long min_ver, SLB_HANDLE *slb, SLB_EXEC *exec);
long dos_slbclose(BASEPAGE *bp, long fn, short nargs, SLB_HANDLE *slb);
long dos_sversion(BASEPAGE *bp, long fn, short nargs);
long dos_syield(BASEPAGE *bp, long fn, short nargs);
long dos_sysconf(BASEPAGE *bp, long fn, short nargs, short n);
long dos_salert(BASEPAGE *bp, long fn, short nargs, const char *msg);
long dos_suptime(BASEPAGE *bp, long fn, short nargs, long *uptime, long *loadaverage);
long dos_sync(BASEPAGE *bp, long fn, short nargs);
long dos_shutdown(BASEPAGE *bp, long fn, short nargs, long mode);
long dos_ssystem(BASEPAGE *bp, long fn, short nargs, short mode, long arg1, long arg2);

long dos_tgetdate(BASEPAGE *bp, long fn, short nargs);
long dos_tsetdate(BASEPAGE *bp, long fn, short nargs, unsigned short date);
long dos_tgettime(BASEPAGE *bp, long fn, short nargs);
long dos_tsettime(BASEPAGE *bp, long fn, short nargs, unsigned short time);
long dos_talarm(BASEPAGE *bp, long fn, short nargs, long time);
long dos_tmalarm(BASEPAGE *bp, long fn, short nargs, long time);
long dos_tsetitimer(BASEPAGE *bp, long fn, short nargs, short which, long *interval, long *value, long *ointerval, long *ovalue);
long dos_tgettimeofday(BASEPAGE *bp, long fn, short nargs, struct timeval *tv, struct timezone *tzp);
long dos_tsettimeofday(BASEPAGE *bp, long fn, short nargs, struct timeval *tv, struct timezone *tzp);

long dos_fcreate(BASEPAGE *bp, long fn, short nargs, const char *fname, short attr);
long dos_fopen(BASEPAGE *bp, long fn, short nargs, const char *fname, short mode);
long dos_fclose(BASEPAGE *bp, long fn, short nargs, short handle);
long dos_fread(BASEPAGE *bp, long fn, short nargs, short handle, long count, void *buf);
long dos_fwrite(BASEPAGE *bp, long fn, short nargs, short handle, long count, const void *buf);
long dos_fdelete(BASEPAGE *bp, long fn, short nargs, const char *fname);
long dos_fseek(BASEPAGE *bp, long fn, short nargs, long offset, short handle, short seekmode);
long dos_fattrib(BASEPAGE *bp, long fn, short nargs, const char *filename, short wflag, short attrib);
long dos_fdup(BASEPAGE *bp, long fn, short nargs, short handle);
long dos_fforce(BASEPAGE *bp, long fn, short nargs, short stdh, short nonstdh);
long dos_frename(BASEPAGE *bp, long fn, short nargs, const char *oldname, const char *newname);
long dos_fdatime(BASEPAGE *bp, long fn, short nargs, _DOSTIME *timeptr, short handle, short wflag);
long dos_flock(BASEPAGE *bp, long fn, short nargs, short handle, short mode, long start, long length);
long dos_fpipe(BASEPAGE *bp, long fn, short nargs, short usrh[2]);
long dos_fcntl(BASEPAGE *bp, long fn, short nargs, short handle, long arg, short cmd);
long dos_finstat(BASEPAGE *bp, long fn, short nargs, short handle);
long dos_foutstat(BASEPAGE *bp, long fn, short nargs, short handle);
long dos_fgetchar(BASEPAGE *bp, long fn, short nargs, short handle, short mode);
long dos_fputchar(BASEPAGE *bp, long fn, short nargs, short handle, long ch, short mode);
long dos_fselect(BASEPAGE *bp, long fn, short nargs, unsigned short timeout, long *rfds, long *wfds, long *xfds);
long dos_fmidipipe(BASEPAGE *bp, long fn, short nargs, short pid, short in, short out);
long dos_fxattr(BASEPAGE *bp, long fn, short nargs, short flag, const char *name, XATTR *xattr);
long dos_flink(BASEPAGE *bp, long fn, short nargs, const char *oldname, const char *newname);
long dos_fsymlink(BASEPAGE *bp, long fn, short nargs, const char *oldname, const char *newname);
long dos_freadlink(BASEPAGE *bp, long fn, short nargs, short bufsiz, char *buf, const char *name);
long dos_fchown(BASEPAGE *bp, long fn, short nargs, const char *name, short uid, short gid);
long dos_fchmod(BASEPAGE *bp, long fn, short nargs, const char *name, short mode);

long dos_mxalloc(BASEPAGE *bp, long fn, short nargs, long amount, short mode);
long dos_mfree(BASEPAGE *bp, long fn, short nargs, void *block);
long dos_mshrink(BASEPAGE *bp, long fn, short nargs, void *block, long newsize);

const char *dos_serror(BASEPAGE *bp, long fn, short nargs, long error);
long dos_fsize(BASEPAGE *bp, long fn, short nargs, const char *fname);
long dos_fexists(BASEPAGE *bp, long fn, short nargs, const char *fname);
long dos_fsearch(BASEPAGE *bp, long fn, short nargs, const char *name, char *fullname, const char *pathvar);
BASEPAGE *dos_pbase(BASEPAGE *bp, long fn, short nargs);
long dos_fload(BASEPAGE *bp, long fn, short nargs, const char *fname, char **buf, long *size, short *mode);
long dos_fsave(BASEPAGE *bp, long fn, short nargs, const char *fname, const void *buf, long size, short mode);
long dos_finfdir(BASEPAGE *bp, long fn, short nargs, char *buf, long blen);
char *dos_getenv(BASEPAGE *bp, long fn, short nargs, const char *var);
long dos_setenv(BASEPAGE *bp, long fn, short nargs, const char *var, const char *value);
long dos_delenv(BASEPAGE *bp, long fn, short nargs, const char *var);
long dos_floadbuf(BASEPAGE *bp, long fn, short nargs, const char *fname, char *buf, long size, short *mode);

/*
 * internal functions
 */
void add_driveu(const char *name, char *buf);
