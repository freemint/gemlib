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


short
do_mdial (MDIAL *dial)
{
	short msg[8], mx, my, mbutton, kstate, kreturn, breturn, event, ret;
	short cont, b, doppel = FALSE;

	ret = -1;
	if (dial != NULL)
	{
		cont = TRUE;
		while (cont)
		{
			event = evnt_multi (MU_MESAG | MU_BUTTON | MU_KEYBD,
					    2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
					    0, 0, msg, 0, &mx, &my, &mbutton,
					    &kstate, &kreturn, &breturn);

			if (event & MU_MESAG)
			{
				switch (msg[0])
				{
				case WM_REDRAW:
				case WM_MOVED:
				case WM_SIZED:
					handle_mdial_msg (msg);
					break;

				case WM_TOPPED:
					/*
					 * if (msg[3] != dial->win_handle)
					 * Bconout(2, 7);
					 */
					/* kein break! */
				case WM_NEWTOP:
				case WM_ONTOP:
					/* immer den Dialog toppen! */
					wind_set (dial->win_handle, WF_TOP, 0,
						  0, 0, 0);
					break;

				case WM_BOTTOMED:
				case 100:	/* WM_M_BACKDROPED MagiC 2.x */
					Bconout (2, 7);
					break;

				case WM_SHADED:
				case WM_UNSHADED:
					dial->is_shaded = !dial->is_shaded;
					break;

				case AP_TERM:	/* sofort verlassen */
					event = 0;
					cont = FALSE;
					dial->next_obj = -1;
					break;
				}
			}

			if ((event & MU_KEYBD) && (!dial->is_shaded))
			{
				cont =
					cf_form_keybd (dial->tree,
						       dial->edit_obj, kstate,
						       &kreturn,
						       &dial->next_obj);
				if (cont)	/* kein Exit-Obj ausgelîst */
				{
					if (kreturn)
						cf_objc_edit (dial->tree,
							      dial->edit_obj,
							      kreturn,
							      &dial->edit_idx,
							      ED_CHAR, kstate,
							      &b);
					else if (cont
						 && (dial->
						     tree[dial->next_obj].
						     ob_flags & OF_EDITABLE))
					{
						/* kein Exit-Obj aber neues Edit-Obj */
						objc_edit (dial->tree,
							   dial->edit_obj, 0,
							   &dial->edit_idx,
							   ED_END);
						dial->edit_obj =
							dial->next_obj;
						objc_edit (dial->tree,
							   dial->edit_obj, 0,
							   &dial->edit_idx,
							   ED_INIT);
					}
				}
			}
			if (event & MU_BUTTON)
			{
				dial->next_obj =
					cf_objc_find (dial->tree, ROOT,
						      MAX_DEPTH, mx, my);
				if (dial->next_obj == -1)
				{
					Bconout (2, 7);
					dial->next_obj = 0;
				}
				else
				{
					doppel = (breturn == 2);
					cont =
						form_button (dial->tree,
							     dial->next_obj,
							     mbutton,
							     &dial->next_obj);
					if (cont
					    && (dial->tree[dial->next_obj].
						ob_flags & OF_EDITABLE))
					{
						/* kein Exit-Obj aber neues Edit-Obj */
						objc_edit (dial->tree,
							   dial->edit_obj, 0,
							   &dial->edit_idx,
							   ED_END);
						dial->edit_obj =
							dial->next_obj;
						/* FIXME: ED_CRSR = ?, Guido.  */
#ifdef ED_CRSR
						if (gl_magx)
							objc_edit (dial->tree,
								   dial->
								   edit_obj,
								   mx,
								   &dial->
								   edit_idx,
								   ED_CRSR);
						else
#endif
							objc_edit (dial->tree,
								   dial->
								   edit_obj,
								   0,
								   &dial->
								   edit_idx,
								   ED_INIT);

					}
				}
			}
		}
		ret = dial->next_obj;
	}
	
	if (doppel)
		ret |= 0x8000;	/* bit 15 fÅr Doppelklick */
	
	return ret;
}
