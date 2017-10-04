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


long dos_cconin(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cconin();
}


void dos_cconout(BASEPAGE *bp, long fn, short nargs, short c)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs > 0)
		Cconout(c);
}


long dos_cauxin(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cauxin();
}


void dos_cauxout(BASEPAGE *bp, long fn, short nargs, short c)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs > 0)
		Cauxout(c);
}


void dos_cprnout(BASEPAGE *bp, long fn, short nargs, short c)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs > 0)
		(void) Cprnout(c);
}


long dos_crawio(BASEPAGE *bp, long fn, short nargs, short c)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Crawio(c);
}


long dos_crawcin(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Crawcin();
}


long dos_cnecin(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cnecin();
}


void dos_cconws(BASEPAGE *bp, long fn, short nargs, const char *str)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs > 0)
		(void) Cconws(str);
}


void dos_cconrs(BASEPAGE *bp, long fn, short nargs, _CCONLINE *buf)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs > 0)
		Cconrs(buf);
}


long dos_cconis(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cconis();
}


long dos_cconos(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cconos();
}


long dos_cprnos(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cprnos();
}


long dos_cauxis(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cauxis();
}


long dos_cauxos(BASEPAGE *bp, long fn, short nargs)
{
	UNUSED(bp);
	UNUSED(fn);
	UNUSED(nargs);
	return Cauxos();
}
