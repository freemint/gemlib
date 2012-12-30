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


/*
 * Dialog vorbereiten.
 */
WDIALOG *
create_wdial_kind (OBJECT *tree, OBJECT *icon, short edit_obj,
		   WDIAL_OCB open_cb, WDIAL_XCB exit_cb, short win_kind)
{
	WDIALOG *new;
	short d;

	if( icon == NULL )
	{
		win_kind &= SMALLER;	/* remove smaller element if no icon */
	}

	new = cf_malloc (sizeof (WDIALOG), "create_wdial", FALSE);
	if (new != NULL)
	{
		/* in die Liste h„ngen */
		new->next = __wdial_list;
		__wdial_list = new;

		new->tree = tree;
		new->icon = icon;
		new->mode = 0;
		new->win_handle = -1;
		new->win_kind = win_kind;

		/*
		 * Titelzeile suchen und als Fenstertitel merken.
		 */
		if (get_magx_obj (tree, 1) == MX_UNDERLINE)
		{
			new->title_obj = 1;
			get_string (tree, new->title_obj, new->win_name);
		}
		else
		{
			new->title_obj = -1;
			strcpy (new->win_name, "*** kein Titel! ***");
		}

		/*
		 * Gibt es ein Abbruch-Button? -> Closer
		 */
		d = find_flag (tree, OF_FLAG11);
		if (d != -1)
			new->cancel_obj = d;
		else
			new->cancel_obj = WD_CLOSER;

		new->next_obj = 0;
		if ((edit_obj <= 0) || !edit_valid (new->tree, edit_obj))
			new->edit_obj = find_edit (new->tree, 0, FMD_FORWARD);
		else
			new->edit_obj = edit_obj;
		new->edit_idx = 0;

		new->open_cb = open_cb;
		new->exit_cb = exit_cb;
	}

	return new;
}

WDIALOG *
create_wdial (OBJECT *tree, OBJECT *icon, short edit_obj,
	      WDIAL_OCB open_cb, WDIAL_XCB exit_cb)
{
	short win_kind;

	if (icon == NULL)
		win_kind = (NAME | MOVER | CLOSER);
	else
		win_kind = (NAME | MOVER | CLOSER | SMALLER );

	return create_wdial_kind (tree, icon, edit_obj, open_cb, exit_cb, win_kind);
}
