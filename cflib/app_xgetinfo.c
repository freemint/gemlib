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


int
appl_xgetinfo (int type, int *out1, int *out2, int *out3, int *out4)
{
	int has_agi = FALSE;

#ifdef __MINT__
	has_agi = ((gl_ap_version == 0x399 && getcookie ("MagX", NULL))
			|| (gl_ap_version >= 0x400)
			|| (appl_find ("?AGI\0\0\0\0") == 0));
#else
	has_agi = ((_GemParBlk.global[0] == 0x399 && getcookie ("MagX", NULL))
			|| (_GemParBlk.global[0] >=  0x400)
			|| (appl_find ("?AGI\0\0\0\0") == 0));
#endif
	if (has_agi)
		return (appl_getinfo (type, out1, out2, out3, out4));
	else
		return 0;
}
