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

#include "kernel32.h"


long dos_fcreate(BASEPAGE *bp, long fn, short nargs, const char *fname, short attr)
{
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	add_driveu(fname, pathbuf);
	return Fcreate(pathbuf, attr);
}


long dos_fopen(BASEPAGE *bp, long fn, short nargs, const char *fname, short mode)
{
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	add_driveu(fname, pathbuf);
	return Fopen(pathbuf, mode);
}


long dos_fclose(BASEPAGE *bp, long fn, short nargs, short handle)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Fclose(handle);
}


long dos_fread(BASEPAGE *bp, long fn, short nargs, short handle, long count, void *buf)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fread(handle, count, buf);
}


long dos_fwrite(BASEPAGE *bp, long fn, short nargs, short handle, long count, const void *buf)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fwrite(handle, count, buf);
}


long dos_fdelete(BASEPAGE *bp, long fn, short nargs, const char *fname)
{
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	add_driveu(fname, pathbuf);
	return Fdelete(pathbuf);
}


long dos_fseek(BASEPAGE *bp, long fn, short nargs, long offset, short handle, short seekmode)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fseek(offset, handle, seekmode);
}


long dos_fattrib(BASEPAGE *bp, long fn, short nargs, const char *filename, short wflag, short attrib)
{
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	add_driveu(filename, pathbuf);
	return Fattrib(pathbuf, wflag, attrib);
}


long dos_fdup(BASEPAGE *bp, long fn, short nargs, short handle)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Fdup(handle);
}


long dos_fforce(BASEPAGE *bp, long fn, short nargs, short stdh, short nonstdh)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Fforce(stdh, nonstdh);
}


long dos_frename(BASEPAGE *bp, long fn, short nargs, const char *oldname, const char *newname)
{
	char oldnamebuf[PATH_MAX];
	char newnamebuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	add_driveu(oldname, oldnamebuf);
	add_driveu(newname, newnamebuf);
	return Frename(0, oldnamebuf, newnamebuf);
}


long dos_fdatime(BASEPAGE *bp, long fn, short nargs, _DOSTIME *timeptr, short handle, short wflag)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fdatime(timeptr, handle, wflag);
}


long dos_flock(BASEPAGE *bp, long fn, short nargs, short handle, short mode, long start, long length)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 3)
		return -EBADARG;
	return Flock(handle, mode, start, length);
}


long dos_fpipe(BASEPAGE *bp, long fn, short nargs, short usrh[2])
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Fpipe(usrh);
}


long dos_fcntl(BASEPAGE *bp, long fn, short nargs, short handle, long arg, short cmd)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fcntl(handle, arg, cmd);
}


long dos_finstat(BASEPAGE *bp, long fn, short nargs, short handle)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Finstat(handle);
}


long dos_foutstat(BASEPAGE *bp, long fn, short nargs, short handle)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Foutstat(handle);
}


long dos_fgetchar(BASEPAGE *bp, long fn, short nargs, short handle, short mode)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Fgetchar(handle, mode);
}


long dos_fputchar(BASEPAGE *bp, long fn, short nargs, short handle, long ch, short mode)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fputchar(handle, ch, mode);
}


long dos_fselect(BASEPAGE *bp, long fn, short nargs, unsigned short timeout, long *rfds, long *wfds, long *xfds)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 3)
		return -EBADARG;
	return Fselect(timeout, rfds, wfds, xfds);
}


long dos_fmidipipe(BASEPAGE *bp, long fn, short nargs, short pid, short in, short out)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fmidipipe(pid, in, out);
}


long dos_fxattr(BASEPAGE *bp, long fn, short nargs, short flag, const char *name, XATTR *xattr)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fxattr(flag, name, xattr);
}


long dos_flink(BASEPAGE *bp, long fn, short nargs, const char *oldname, const char *newname)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Flink(oldname, newname);
}


long dos_fsymlink(BASEPAGE *bp, long fn, short nargs, const char *oldname, const char *newname)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Fsymlink(oldname, newname);
}


long dos_freadlink(BASEPAGE *bp, long fn, short nargs, short bufsiz, char *buf, const char *name)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Freadlink(bufsiz, buf, name);
}


long dos_fchown(BASEPAGE *bp, long fn, short nargs, const char *name, short uid, short gid)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Fchown(name, uid, gid);
}


long dos_fchmod(BASEPAGE *bp, long fn, short nargs, const char *name, short mode)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Fchmod(name, mode);
}
