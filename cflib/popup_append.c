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

#include "intern.h"


short
append_popup (POPUP *p, char *item)
{
	char *text;
	int i, state;

	if (p->tree == NULL)
		return FALSE;

	if (p->akt_item >= p->max_item)
		return FALSE;

	/* letztes wird vorletztes */
	p->tree[p->akt_item].ob_next = p->akt_item + 1;
	p->tree[p->akt_item].ob_flags = OF_SELECTABLE;

	p->akt_item++;

	if (item[0] == '-')
		state = 0x0008;
	else
		state = 0x0000;

	/* Speicher fr String holen */
	text = strdup (item);
	if (text == NULL)
		return FALSE;

	/* neues */
	p->tree[p->akt_item].ob_next = 0;
	p->tree[p->akt_item].ob_head = -1;
	p->tree[p->akt_item].ob_tail = -1;
	p->tree[p->akt_item].ob_type = G_STRING;
	p->tree[p->akt_item].ob_flags = (OF_SELECTABLE | OF_LASTOB);
	p->tree[p->akt_item].ob_state = state;
	p->tree[p->akt_item].ob_spec.free_string = text;
	p->tree[p->akt_item].ob_x = 0;
	p->tree[p->akt_item].ob_y = (p->akt_item - 1) * gl_hchar;
	p->tree[p->akt_item].ob_width = (p->item_len) * gl_wchar;
	p->tree[p->akt_item].ob_height = 1 * gl_hchar;

	/* Box */
	p->tree[0].ob_tail = p->akt_item;
	p->tree[0].ob_height = (p->akt_item) * gl_hchar;

	for (i = 0; i <= p->akt_item; i++)
	{
		/* zurck auf Zeichenkoor., damit der obfix klappt! */
		p->tree[i].ob_y /= gl_hchar;
		p->tree[i].ob_width /= gl_wchar;
		p->tree[i].ob_height /= gl_hchar;
		rsrc_obfix (p->tree, i);
	}
	return TRUE;
}
