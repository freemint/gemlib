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


short
key_wdial (short kreturn, short kstate)
{
	short wh, d;
	short ret = TRUE, cont, ctrl;
	WDIALOG *wd;

	wind_get (0, WF_TOP, &wh, &d, &d, &d);
	wd = get_wdial (wh);
	if (wd != NULL && wd->mode == WD_OPEN)
	{
		cont = cf_form_keybd (wd->tree, wd->edit_obj, kstate,
				       &kreturn, &wd->next_obj);
		if (cont)
		{
			if (wd->next_obj > 0 && wd->next_obj != wd->edit_obj && (wd->tree[wd->next_obj].ob_flags & OF_EDITABLE))
			{
				objc_edit (wd->tree, wd->edit_obj, 0,
					   &wd->edit_idx, ED_END);
				wd->edit_obj = wd->next_obj;
				wd->edit_idx = -1;
				objc_edit (wd->tree, wd->edit_obj, 0,
					   &wd->edit_idx, ED_INIT);
			}
			if (kreturn)
				cf_objc_edit (wd->tree, wd->edit_obj, kreturn,
					      &wd->edit_idx, ED_CHAR, kstate,
					      &ctrl);
		}
		else
			wdial_call_cb (wd);

		/* alle Ctrl-Codes auer ^X^C^V werden nicht ausgewertet */
		if ((kstate & K_CTRL) && !ctrl)
			ret = FALSE;
	}
	else
		ret = FALSE;

	return ret;
}
