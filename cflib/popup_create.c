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


/*
 * Popup zur Laufzeit erzeugen.
 */
short
create_popup (POPUP *p, short anz, short maxlen, char *item)
{
	char *text;
	int i;

	p->tree = cf_malloc ((anz + 1) * sizeof (OBJECT), "create_popup", FALSE);
	if (p->tree == NULL)
		return FALSE;

	p->max_item = anz;
	if (maxlen == -1)
		p->item_len = (int) strlen (item);
	else
		p->item_len = maxlen;

	/* Box */
	p->tree[0].ob_next = -1;
	p->tree[0].ob_head = 1;
	p->tree[0].ob_tail = 1;
	p->tree[0].ob_type = G_BOX;
	p->tree[0].ob_flags = OF_FL3DBAK;
	p->tree[0].ob_state = OS_SHADOWED;
	p->tree[0].ob_spec.index = 0x00ff1100L;	/* Rahmen, Farbe ... */
	p->tree[0].ob_x = 0;
	p->tree[0].ob_y = 0;
	p->tree[0].ob_width = p->item_len;
	p->tree[0].ob_height = 1;

	/* Speicher fr String holen */
	text = strdup (item);
	if (text == NULL)
		return FALSE;

	/* 1. Eintrag */
	p->tree[1].ob_next = 0;
	p->tree[1].ob_head = -1;
	p->tree[1].ob_tail = -1;
	p->tree[1].ob_type = G_STRING;
	p->tree[1].ob_flags = (OF_SELECTABLE | OF_LASTOB);
	p->tree[1].ob_state = 0;
	p->tree[1].ob_spec.free_string = text;
	p->tree[1].ob_x = 0;
	p->tree[1].ob_y = 0;
	p->tree[1].ob_width = p->item_len;
	p->tree[1].ob_height = 1;

	p->akt_item = 1;

	for (i = 0; i <= p->akt_item; i++)
		rsrc_obfix (p->tree, i);

	return TRUE;
}
