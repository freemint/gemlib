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


/*
 * these are not optional and cannot be set
 * to zero in the header, even if they
 * currently don't do anything
 */
long kernel32_init(void)
{
	return 0;
}


void kernel32_exit(void)
{
}


long kernel32_open(BASEPAGE *bp)
{
	UNUSED(bp);
	return 0;
}


void kernel32_close(BASEPAGE *bp)
{
	UNUSED(bp);
}
