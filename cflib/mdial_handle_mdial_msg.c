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

#include <osbind.h>
#include "mdial.h"


static inline void
redraw_cursor (MDIAL *dial)
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

static inline void
move_dial (MDIAL *dial, short x, short y)
{
	GRECT r;

	wind_get_grect (dial->win_handle, WF_CURRXYWH, &r);
	r.g_x = x;
	r.g_y = y;
	wind_set_grect (dial->win_handle, WF_CURRXYWH, &r);
	wind_get_grect (dial->win_handle, WF_WORKXYWH, &r);
	dial->tree[0].ob_x = r.g_x;
	dial->tree[0].ob_y = r.g_y - dial->delta_y;
}

static short
handle_msg (short *msg)
{
	MDIAL *md;
	short ret = FALSE;

	md = __mdial_md_list;
	while (md)
	{
		if (msg[3] == md->win_handle)
			break;
		md = md->next;
	}
	if (md)
	{
		switch (msg[0])
		{
		case WM_REDRAW:
			redraw_mdial (md, ROOT, MAX_DEPTH, msg[4], msg[5],
				      msg[6], msg[7]);
			redraw_cursor (md);
			ret = TRUE;
			break;

		case WM_MOVED:
			move_dial (md, msg[4], msg[5]);
			ret = TRUE;
			break;
		}
	}
	return ret;
}

void
handle_mdial_msg (short *msg)
{
	if (!handle_msg (msg) && __mdial_win_cb)
	{
		switch (msg[0])
		{
		case WM_REDRAW:
		case WM_MOVED:
		case WM_SIZED:
			__mdial_win_cb (msg);
			break;
		default:
			;
		}
	}
}
