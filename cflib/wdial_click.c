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


int
click_wdial (int clicks, int x, int y, int kshift, int mbutton)
{
	int wh;
	int ret = TRUE, cont;
	int obj;
	WDIALOG *wd;

	wh = wind_find (x, y);
	wd = get_wdial (wh);
	if (wd != NULL && wd->mode == WD_OPEN)
	{
		if (mbutton == 1)
		{
			obj = cf_objc_find (wd->tree, ROOT, MAX_DEPTH, x, y);
			if (obj > -1)
			{
				cont =
					form_button (wd->tree, obj, clicks,
						     &wd->next_obj);
				if (cont
				    &&
				    (get_flag
				     (wd->tree, wd->next_obj, EDITABLE)))
				{
					objc_edit (wd->tree, wd->edit_obj, 0,
						   &wd->edit_idx, ED_END);
					wd->edit_obj = wd->next_obj;
#ifdef ED_CRSR
					if (gl_magx)
						objc_edit (wd->tree,
							   wd->edit_obj, x,
							   &wd->edit_idx,
							   ED_CRSR);
					else
#endif
						objc_edit (wd->tree,
							   wd->edit_obj, 0,
							   &wd->edit_idx,
							   ED_INIT);
				}
				else if (!cont)
				{
					if (clicks == 2)
						wd->next_obj |= 0x8000;
					wdial_call_cb (wd);
				}
			}
			else
				Bconout (2, 7);
		}
		else if (mbutton == 2)	/* Rechtsklick ignorieren */
			ret = TRUE;
	}
	else
		ret = FALSE;
	return ret;
}
