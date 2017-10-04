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

#ifndef DOSFUNC
# error "DOSFUNC must be defined before including this file"
#endif

	DOSFUNC(pterm0)
	DOSFUNC(cconin)
	DOSFUNC(cconout)
	DOSFUNC(cauxin)
	DOSFUNC(cauxout)
	DOSFUNC(cprnout)
	DOSFUNC(crawio)
	DOSFUNC(crawcin)
	DOSFUNC(cnecin)
	DOSFUNC(cconws)
	DOSFUNC(cconrs)
	DOSFUNC(cconis)
	NOFUNC
	NOFUNC
	DOSFUNC(dsetdrv)
	NOFUNC
	DOSFUNC(cconos)
	DOSFUNC(cprnos)
	DOSFUNC(cauxis)
	DOSFUNC(cauxos)
	NOFUNC /* Maddalt */
	DOSFUNC(srealloc)
	DOSFUNC(slbopen)
	DOSFUNC(slbclose)
	NOFUNC
	DOSFUNC(dgetdrv)
	NOFUNC /* Fsetdta */
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC /* Super */
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	DOSFUNC(tgetdate)
	DOSFUNC(tsetdate)
	DOSFUNC(tgettime)
	DOSFUNC(tsettime)
	NOFUNC
	NOFUNC /* Fgetdta */
	DOSFUNC(sversion)
	NOFUNC /* Ptermres */
	NOFUNC
	NOFUNC /* Sconfig */
	NOFUNC
	NOFUNC
	DOSFUNC(dfree)
	NOFUNC
	NOFUNC
	DOSFUNC(dcreate)
	DOSFUNC(ddelete)
	DOSFUNC(dsetpath)
	DOSFUNC(fcreate)
	DOSFUNC(fopen)
	DOSFUNC(fclose)
	DOSFUNC(fread)
	DOSFUNC(fwrite)
	DOSFUNC(fdelete)
	DOSFUNC(fseek)
	DOSFUNC(fattrib)
	DOSFUNC(mxalloc)
	DOSFUNC(fdup)
	DOSFUNC(fforce)
	DOSFUNC(dgetpath)
	NOFUNC /* Malloc */
	DOSFUNC(mfree)
	DOSFUNC(mshrink)
	DOSFUNC(pexec)
	DOSFUNC(pterm)
	NOFUNC
	NOFUNC /* Fsfirst */
	NOFUNC /* Fsnext */
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	DOSFUNC(frename)
	DOSFUNC(fdatime)
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	DOSFUNC(flock)
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	DOSFUNC(syield)
	DOSFUNC(fpipe)
	NOFUNC /* Ffchown */
	NOFUNC /* Ffchmod */
	NOFUNC /* Fsync */
	DOSFUNC(fcntl)
	DOSFUNC(finstat)
	DOSFUNC(foutstat)
	DOSFUNC(fgetchar)
	DOSFUNC(fputchar)
	DOSFUNC(pwait)
	DOSFUNC(pnice)
	DOSFUNC(pgetpid)
	DOSFUNC(pgetppid)
	DOSFUNC(pgetpgrp)
	DOSFUNC(psetpgrp)
	DOSFUNC(pgetuid)
	DOSFUNC(psetuid)
	DOSFUNC(pkill)
	DOSFUNC(psignal)
	DOSFUNC(pvfork)
	DOSFUNC(pgetgid)
	DOSFUNC(psetgid)
	DOSFUNC(psigblock)
	DOSFUNC(psigsetmask)
	DOSFUNC(pusrval)
	DOSFUNC(pdomain)
	DOSFUNC(psigreturn)
	DOSFUNC(pfork)
	DOSFUNC(pwait3)
	DOSFUNC(fselect)
	DOSFUNC(prusage)
	DOSFUNC(psetlimit)
	DOSFUNC(talarm)
	DOSFUNC(pause)
	DOSFUNC(sysconf)
	DOSFUNC(psigpending)
	DOSFUNC(dpathconf)
	DOSFUNC(pmsg)
	DOSFUNC(fmidipipe)
	DOSFUNC(prenice)
	DOSFUNC(dopendir)
	DOSFUNC(dreaddir)
	DOSFUNC(drewinddir)
	DOSFUNC(dclosedir)
	DOSFUNC(fxattr)
	DOSFUNC(flink)
	DOSFUNC(fsymlink)
	DOSFUNC(freadlink)
	DOSFUNC(dcntl)
	DOSFUNC(fchown)
	DOSFUNC(fchmod)
	DOSFUNC(pumask)
	DOSFUNC(psemaphore)
	DOSFUNC(dlock)
	DOSFUNC(psigpause)
	DOSFUNC(psigaction)
	DOSFUNC(pgeteuid)
	DOSFUNC(pgetegid)
	DOSFUNC(pwaitpid)
	DOSFUNC(dgetcwd)
	DOSFUNC(salert)
	DOSFUNC(tmalarm)
	NOFUNC /* was Psigintr */
	DOSFUNC(suptime)
	NOFUNC /* Ptrace */
	NOFUNC /* Mvalidate */
	DOSFUNC(dxreaddir)
	DOSFUNC(pseteuid)
	DOSFUNC(psetegid)
	DOSFUNC(pgetauid)
	DOSFUNC(psetauid)
	DOSFUNC(pgetgroups)
	DOSFUNC(psetgroups)
	DOSFUNC(tsetitimer)
	NOFUNC /* was Scookie/now Dchroot */
	NOFUNC /* Fstat64 */
	NOFUNC /* Fseek64 */
	NOFUNC /* Dsetkey */
	DOSFUNC(psetreuid)
	DOSFUNC(psetregid)
	DOSFUNC(sync)
	DOSFUNC(shutdown)
	DOSFUNC(dreadlabel)
	DOSFUNC(dwritelabel)
	DOSFUNC(ssystem)
	DOSFUNC(tgettimeofday)
	DOSFUNC(tsettimeofday)
	NOFUNC /* Tadjtime */
	DOSFUNC(pgetpriority)
	DOSFUNC(psetpriority)
	NOFUNC /* Fpoll */
	NOFUNC /* Fwritev */
	NOFUNC /* Freadv */
	NOFUNC /* Ffstat64 */
	NOFUNC /* Psysctl */
	NOFUNC /* Pemulation */
	NOFUNC /* Fsocket */
	NOFUNC /* Fsocketpair */
	NOFUNC /* Faccept */
	NOFUNC /* Fconnect */
	NOFUNC /* Fbind */
	NOFUNC /* Flisten */
	NOFUNC /* Frecvmesg */
	NOFUNC /* Fsendmsg */
	NOFUNC /* Frecvfrom */
	NOFUNC /* Fsendto */
	NOFUNC /* Fsetsockopt */
	NOFUNC /* Fgetsockopt */
	NOFUNC /* Fgetpeername */
	NOFUNC /* Fgetsockname */
	NOFUNC /* Fshutdown */
	NOFUNC /* Pshmget */
	NOFUNC /* Pshmctl */
	NOFUNC /* Pshmat */
	NOFUNC /* Pshmdt */
	NOFUNC /* Psemget */
	NOFUNC /* Psemctl */
	NOFUNC /* Psemop */
	NOFUNC /* Psemconfig */
	NOFUNC /* Pmsgget */
	NOFUNC /* Pmsgctl */
	NOFUNC /* Pmsgget */
	NOFUNC /* Pmsgsnd */
	NOFUNC /* Pmsgrcv */
	NOFUNC
	NOFUNC /* Maccess */
	NOFUNC
	NOFUNC
	NOFUNC /* Fchown16 */
	NOFUNC /* Fchdir */
	NOFUNC /* Ffdopendir */
	NOFUNC /* Fdirfd */
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC
	LIBFUNC(serror)
	LIBFUNC(fsize)
	LIBFUNC(fexists)
	LIBFUNC(fsearch)
	LIBFUNC(pbase)
	LIBFUNC(fload)
	LIBFUNC(fsave)
	LIBFUNC(finfdir)
	LIBFUNC(getenv)
	LIBFUNC(setenv)
	LIBFUNC(delenv)
	LIBFUNC(floadbuf)
	NOFUNC
	NOFUNC
	NOFUNC
	NOFUNC

#undef DOSFUNC
#undef LIBFUNC
#undef NOFUNC
