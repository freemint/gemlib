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


long dos_mxalloc(BASEPAGE *bp, long fn, short nargs, long amount, short mode)
{
	long ret = -EFAULT;
	
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	if (amount != 0)
		ret = (long)Mxalloc(amount, mode);
	if (ret == 0)
		ret = -EFAULT; /* WTF? */
	return ret;
}


long dos_mfree(BASEPAGE *bp, long fn, short nargs, void *block)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 0)
		return -EBADARG;
	return Mfree(block);
}


long dos_mshrink(BASEPAGE *bp, long fn, short nargs, void *block, long newsize)
{
	UNUSED(bp);
	UNUSED(fn);
	if (nargs <= 1)
		return -EBADARG;
	if ((long)block <= 0 || newsize <= 0)
		return -EFAULT;
	return Mshrink(block, newsize);
}
