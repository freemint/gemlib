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


long dos_srealloc(BASEPAGE *bp, long fn, short nargs, long len)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Srealloc(len);
}


long dos_slbclose(BASEPAGE *bp, long fn, short nargs, SLB_HANDLE *slb)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Slbclose(slb);
}


long dos_slbopen(BASEPAGE *bp, long fn, short nargs, const char *name, const char *path, long min_ver, SLB_HANDLE *slb, SLB_EXEC *exec)
{
	char namebuf[PATH_MAX];
	char pathbuf[PATH_MAX];
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 4)
		return -EBADARG;
	add_driveu(name, namebuf);
	if (path != NULL)
	{
		add_driveu(path, pathbuf);
		path = pathbuf;
	}
	return Slbopen(namebuf, path, min_ver, slb, exec);
}


long dos_sversion(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Sversion();
}


long dos_syield(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Syield();
}


long dos_sysconf(BASEPAGE *bp, long fn, short nargs, short n)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Sysconf(n);
}


long dos_salert(BASEPAGE *bp, long fn, short nargs, const char *msg)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Salert(msg);
}


long dos_suptime(BASEPAGE *bp, long fn, short nargs, long *uptime, long *loadaverage)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Suptime(uptime, loadaverage);
}


long dos_sync(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Sync();
}


long dos_shutdown(BASEPAGE *bp, long fn, short nargs, long mode)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Shutdown(mode);
}


long dos_ssystem(BASEPAGE *bp, long fn, short nargs, short mode, long arg1, long arg2)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 2)
		return -EBADARG;
	return Ssystem(mode, arg1, arg2);
}
