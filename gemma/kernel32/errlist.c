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
#include "errlist.h"


const char *dos_serror(BASEPAGE *bp, long fn, short nargs, long error)
{
	short i;
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return "[Wrong call to kernel.slb]";
	if (error != 0)
	{
		for (i = 0; errorlist[i].code != 0; i++)
		{
			if (errorlist[i].code == error)
				return errorlist[i].text;
		}
		return "Unknown error";
	}
	return "No errors";
}
