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


long dos_dsetdrv(BASEPAGE *bp, long fn, short nargs, short drv)
{
	UNUSED(bp);
	UNUSED(fn);
	if ((short)nargs <= 0)
		return -EBADARG;
	return Dsetdrv(drv);
}


long dos_dgetdrv(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Dgetdrv();
}


long dos_dfree(BASEPAGE *bp, long fn, short nargs, _DISKINFO *buf, short drv)
{
	UNUSED(bp);
	UNUSED(fn);
	if ((short)nargs <= 1)
		return -EBADARG;
	return Dfree(buf, drv);
}


long dos_dcreate(BASEPAGE *bp, long fn, short nargs, const char *path)
{
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if ((short)nargs <= 0)
		return -EBADARG;
	add_driveu(path, pathbuf);
	return Dcreate(pathbuf);
}


long dos_ddelete(BASEPAGE *bp, long fn, short nargs, const char *path)
{
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if ((short)nargs <= 0)
		return -EBADARG;
	add_driveu(path, pathbuf);
	return Ddelete(pathbuf);
}


long dos_dsetpath(BASEPAGE *bp, long fn, short nargs, const char *path)
{
	char pathbuf[PATH_MAX];
	short olddrv;
	long ret;
	
	UNUSED(bp);
	UNUSED(fn);
	if ((short)nargs <= 0)
		return -EBADARG;
	add_driveu(path, pathbuf);
	if (pathbuf[1] == ':')
	{
		olddrv = dos_dgetdrv(bp, fn, (short)SLB_NARGS(0));
		/* WTF? Dsetdrv needs a drive number, not a drive letter */
		if ((ret = dos_dsetdrv(bp, fn, (short)SLB_NARGS(1), pathbuf[0])) == 0)
		{
			ret = Dsetpath(pathbuf + 2);
		}
		dos_dsetdrv(bp, fn, (short)SLB_NARGS(1), olddrv);
		if (ret == 0)
			return 0;
	}
	return Dsetpath(pathbuf);
}


long dos_dgetpath(BASEPAGE *bp, long fn, short nargs, char *path, short drv)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Dgetpath(path, drv);
}


long dos_dpathconf(BASEPAGE *bp, long fn, short nargs, const char *path, short mode)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Dpathconf(path, mode);
}


long dos_dopendir(BASEPAGE *bp, long fn, short nargs, const char *path, short flag)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Dopendir(path, flag);
}


long dos_dreaddir(BASEPAGE *bp, long fn, short nargs, short len, long dirhandle, char *buf)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Dreaddir(len, dirhandle, buf);
}


long dos_drewinddir(BASEPAGE *bp, long fn, short nargs, long dirhandle)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Drewinddir(dirhandle);
}


long dos_dclosedir(BASEPAGE *bp, long fn, short nargs, long dirhandle)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Dclosedir(dirhandle);
}


long dos_dcntl(BASEPAGE *bp, long fn, short nargs, short cmd, const char *name, long arg)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Dcntl(cmd, name, arg);
}


long dos_dlock(BASEPAGE *bp, long fn, short nargs, short mode, short drv)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Dlock(mode, drv);
}


long dos_dgetcwd(BASEPAGE *bp, long fn, short nargs, char *path, short drv, short size)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Dgetcwd(path, drv, size);
}


long dos_dxreaddir(BASEPAGE *bp, long fn, short nargs, short in, long dirhandle, char *buf, XATTR *xattr, long *xr)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 4)
		return -EBADARG;
	return Dxreaddir(in, dirhandle, buf, xattr, xr);
}


long dos_dreadlabel(BASEPAGE *bp, long fn, short nargs, const char *path, char *label, short length)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Dreadlabel(path, label, length);
}


long dos_dwritelabel(BASEPAGE *bp, long fn, short nargs, const char *path, const char *label)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Dwritelabel(path, label);
}
