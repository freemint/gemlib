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

#include "mdial.h"


void
redraw_mdial (MDIAL * dial, short start, short depth, short x, short y, short w, short h)
{
	GRECT r, r1;

	r.g_x = x;
	r.g_y = y;
	r.g_w = w;
	r.g_h = h;
	wind_update (BEG_UPDATE);
	hide_mouse_if_needed (&r);
	wind_get_grect (dial->win_handle, WF_FIRSTXYWH, &r1);
	while (r1.g_w != 0 && r1.g_h != 0)
	{
		if (rc_intersect (&r, &r1))
			objc_draw (dial->tree, start, depth, r1.g_x, r1.g_y,
				   r1.g_w, r1.g_h);
		wind_get_grect (dial->win_handle, WF_NEXTXYWH, &r1);
	}
	show_mouse ();
	wind_update (END_UPDATE);
}
