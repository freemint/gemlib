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

#include <ctype.h>
#include <stddef.h>

#include "intern.h"
#include "magx.h"


short
get_magx_shortcut (OBJECT *tree, short obj, char *c)
{
	short pos = -1, us, mtyp;
	char *p;

	if (c != NULL)
		*c = '\0';
	mtyp = get_magx_obj (tree, obj);

	if ((mtyp == MX_SCRADIO) || (mtyp == MX_SCCHECK) ||
	    (mtyp == MX_SCEXIT) || (mtyp == MX_SCSTRING))
	{
		if ((tree[obj].ob_type & 0x00ff) == G_USERDEF)
			p = (char *) tree[obj].ob_spec.userblk->ub_parm;
		else
			p = tree[obj].ob_spec.free_string;
		us = (tree[obj].ob_state & 0xff00) >> 8;
		if (us != 0xFF)
		{
			pos = us & 0xf;
			if (c != NULL)
				*c = p[pos];
		}
	}
	
	return pos;
}
