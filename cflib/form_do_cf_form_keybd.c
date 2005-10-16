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

/*
 * Ein eigener form_do(), der einige Sondertastentasten kann:
 * 
 * HELP     Button mit Flag11
 * UNDO     Button mit Flag12
 * ^C^V^X   Klemmbrett in Editfeldern
 * ALT-X    MagiC-Shortcut
 *
 */

#include "intern.h"


static KEY_CB key_cb = NULL;

short
cf_form_keybd (OBJECT *tree, short edit_obj, short kstate, short *kreturn,
	       short *next_obj)
{
	short cont = TRUE, obj;
	short scan;

	if (key_cb != NULL)
	{
		cont = (*key_cb) (tree, edit_obj, kstate, kreturn, next_obj);
		if (!cont || *kreturn == 0)
			return cont;
		else
			cont = TRUE;
	}

	/*
	 * Ozk: XaAES have decent shortcut support, so we use that when XaAES
	 *      is detected.
	 */
	if (!gl_xaaes)
	{
		obj = find_shortcut (tree, kstate, *kreturn);

		if (obj != -1)
		{
			*kreturn = 0;
			cont = form_button (tree, obj, 1, next_obj);
			return cont;
		}
		scan = (*kreturn & 0xFF00) >> 8;
	}
	

	cont = form_keybd (tree, edit_obj, *next_obj, *kreturn, next_obj,
			    kreturn);

	/*
	 * Ozk: This problem is not present under XaAES!
	 */
	if (!gl_xaaes)
	{
		/*
		 * Den eventuellen Wechsel des Editfelds mit Cursor/TAB bernehmen wir
		 * selbst, da das AES auch HIDDEN oder DISABLE Felder anspringt!
		 * Auerdem werten wir dann gleich noch Shift-TAB mit aus.
		 */
		if ((scan == 0x48) || ((kstate & K_SHIFT) && scan == 0x0F))	/* UP, TAB */
			*next_obj = find_edit (tree, edit_obj, FMD_BACKWARD);
		else if ((scan == 0x50) || (scan == 0x0F))	/* DOWN, TAB */
			*next_obj = find_edit (tree, edit_obj, FMD_FORWARD);
	}
	return cont;
}

KEY_CB
set_formdo_keycb (KEY_CB new)
{
	KEY_CB old;

	old = key_cb;
	key_cb = new;
	return old;
}
