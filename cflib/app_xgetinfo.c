/*
 * CFLIB, a GEM library for ATARI/TOS
 * Copyright (C) 1999, 2000 Christian Felsch
 * 
 * Modified for FreeMiNT CVS by Frank Naumann <fnaumann@freemint.de>
 * 
 * Please send suggestions, patches or bug reports to me or
 * the MiNT mailing list.
 * 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 * 
 */

#include "intern.h"
#include "app.h"

#if ! (( __GEMLIB_MAJOR__ > 0 ) || ( __GEMLIB_MINOR__ > 42 ) || (( __GEMLIB_MINOR__ == 42 ) && ( __GEMLIB_REVISION__ > 2 )))
/* note: The new gemlib plXX (after the mgemlib->gemlib merge)
 * contains correct appl_xgetinfo() binding already */

short
appl_xgetinfo (short type, short *out1, short *out2, short *out3, short *out4)
{
	short has_agi = FALSE;

	has_agi = (	(_GemParBlk.global[0] >= 0x400)
			|| (appl_find ("?AGI\0\0\0\0") == 0));
	if (has_agi)
		return (appl_getinfo (type, out1, out2, out3, out4));

	return 0;
}

#endif
