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


void
get_string (OBJECT *tree, short obj, char *text)
{
	long spec;
	int type;

	spec = get_obspec (tree, obj);
	type = get_obtype (tree, obj, NULL);
	switch (type)
	{
		case G_BUTTON:
		case G_STRING:
		case G_TITLE:
#ifdef G_SHORTCUT
		case G_SHORTCUT:
#endif
			strcpy (text, (char *) spec);
			break;

		case G_CICON:
		case G_ICON:
			strcpy (text, ((ICONBLK *) spec)->ib_ptext);
			break;

		case G_TEXT:
		case G_BOXTEXT:
		case G_FTEXT:
		case G_FBOXTEXT:
			strcpy (text, ((TEDINFO *) spec)->te_ptext);
			break;

		default:
		{
			char s[96];

			sprintf (s,
				 "[3][CF-Lib Panic: get_string()!|Objekt %d hat unbekannten Typ %d|!][Abbruch]",
				 obj, type);
			form_alert (1, s);
		}
			text[0] = '0';
			break;
	}
}
