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


void
iconify_wdial (WDIALOG * wd, int x, int y, int w, int h)
{
	if (wd->icon && !(wd->mode & WD_ICON))
	{
		/* alte Gr”že merken */
		wind_get_grect (wd->win_handle, WF_CURRXYWH, &wd->work);

		wind_set (wd->win_handle, WF_ICONIFY, x, y, w, h);
		wind_get (wd->win_handle, WF_WORKXYWH, &x, &y, &w, &h);
		wd->icon[0].ob_x = x;
		wd->icon[0].ob_y = y;
		wd->icon[0].ob_width = w;
		wd->icon[0].ob_height = h;
		wd->icon[1].ob_x = (w - wd->icon[1].ob_width) / 2;
		wd->icon[1].ob_y = (h - wd->icon[1].ob_height) / 2;
		wd->mode |= WD_ICON;
	}
}
