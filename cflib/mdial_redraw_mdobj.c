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


static inline void
redraw_cursor (MDIAL * dial)
{
	if (dial->edit_obj > 0)
	{
		GRECT r;

		objc_edit (dial->tree, dial->edit_obj, 0, &dial->edit_idx,
			   ED_INIT);
		get_objframe (dial->tree, dial->edit_obj, &r);
		redraw_mdial (dial, ROOT, MAX_DEPTH, r.g_x, r.g_y - 3,
			      r.g_w + 1, r.g_h + 6);
		objc_edit (dial->tree, dial->edit_obj, 0, &dial->edit_idx,
			   ED_INIT);
	}
}

void
redraw_mdobj (MDIAL * dial, int obj)
{
	GRECT r;

	if (dial != NULL)
	{
		get_objframe (dial->tree, obj, &r);
		redraw_mdial (dial, ROOT, MAX_DEPTH, r.g_x, r.g_y - 3,
			      r.g_w + 1, r.g_h + 6);

		/* neu zeichnen, wenn obj das Editfeld bzw. ein Child von obj ist */
		if ((obj == dial->edit_obj)
			|| (dial->edit_obj >= dial->tree[obj].ob_head
				&& dial->edit_obj <= dial->tree[obj].ob_tail))
		{
			redraw_cursor (dial);
		}
	}
}
