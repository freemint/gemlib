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


long dos_tgetdate(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Tgetdate();
}


long dos_tsetdate(BASEPAGE *bp, long fn, short nargs, unsigned short date)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Tsetdate(date);
}


long dos_tgettime(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Tgettime();
}


long dos_tsettime(BASEPAGE *bp, long fn, short nargs, unsigned short timeval)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Tsettime(timeval);
}


long dos_talarm(BASEPAGE *bp, long fn, short nargs, long timeval)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Talarm(timeval);
}


long dos_tmalarm(BASEPAGE *bp, long fn, short nargs, long timeval)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Tmalarm(timeval);
}


long dos_tsetitimer(BASEPAGE *bp, long fn, short nargs, short which, long *interval, long *value, long *ointerval, long *ovalue)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 4)
		return -EBADARG;
	return Tsetitimer(which, interval, value, ointerval, ovalue);
}


long dos_tgettimeofday(BASEPAGE *bp, long fn, short nargs, struct timeval *tv, struct timezone *tzp)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Tgettimeofday(tv, tzp);
}


long dos_tsettimeofday(BASEPAGE *bp, long fn, short nargs, struct timeval *tv, struct timezone *tzp)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	return Tsettimeofday(tv, tzp);
}
