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

#include "wdial.h"


static inline void
move_wdial (WDIALOG * wd, int new_x, int new_y)
{
	if (wd != NULL)
	{
		GRECT r;

		wind_get_grect (wd->win_handle, WF_CURRXYWH, &r);
		r.g_x = new_x;
		r.g_y = new_y;
		wind_set_grect (wd->win_handle, WF_CURRXYWH, &r);
		wind_get_grect (wd->win_handle, WF_WORKXYWH, &r);

		if (wd->mode & WD_ICON)
		{
			wd->icon[0].ob_x = r.g_x;
			wd->icon[0].ob_y = r.g_y;
		}
		else
		{
			wd->tree[0].ob_x = r.g_x;
			wd->tree[0].ob_y = r.g_y - wd->delta_y;
			wd->work.g_x = r.g_x;
			wd->work.g_y = r.g_y;
			wd->work.g_w = r.g_w;
			wd->work.g_h = r.g_h;
		}
	}
}

/*
 * Event-Verarbeitung.
 */
int
message_wdial (int *msg)
{
	int ret = TRUE;
	WDIALOG *wd;

	wd = get_wdial (msg[3]);
	if (wd != NULL)
	{
		switch (msg[0])
		{
		case WM_REDRAW:
			draw_wdial (wd, ROOT, MAX_DEPTH, msg[4], msg[5],
				    msg[6], msg[7]);
			wdial_draw_cursor (wd, ED_INIT);
			break;

		case WM_MOVED:
			move_wdial (wd, msg[4], msg[5]);
			break;

		case WM_TOPPED:
			wind_set (wd->win_handle, WF_TOP, 0, 0, 0, 0);
			break;

		case WM_BOTTOMED:
			wind_set (wd->win_handle, WF_BOTTOM, 0, 0, 0, 0);
			break;

		case WM_ICONIFY:
			iconify_wdial (wd, msg[4], msg[5], msg[6], msg[7]);
			break;

		case WM_UNICONIFY:
			uniconify_wdial (wd, msg[4], msg[5], msg[6], msg[7]);
			break;

		case WM_SHADED:
			wd->mode |= WD_SHADE;
			break;

		case WM_UNSHADED:
			wd->mode &= ~WD_SHADE;
			break;

		case WM_CLOSED:
			wd->next_obj = wd->cancel_obj;
			wdial_call_cb (wd);
			break;

		case WM_UNTOPPED:
		case WM_ONTOP:
		case WM_NEWTOP:
			/* ignore */
			break;

		default:
			ret = FALSE;
		}
	}
	else
		ret = FALSE;
	return ret;
}
