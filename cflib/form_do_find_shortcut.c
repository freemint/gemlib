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

#include <ctype.h>
#include "intern.h"


int
find_shortcut (OBJECT * tree, int kstate, int kreturn)
{
	static KEYTAB *keytab = NULL;
	int ret = -1;
	int scan;

	if (keytab == NULL)
		keytab =
			(KEYTAB *) Keytbl ((void *) -1, (void *) -1,
					   (void *) -1);

	scan = (kreturn & 0xFF00) >> 8;

	if (scan == 0x62)	/* HELP */
		ret = find_flag (tree, FLAG12);

	else if (scan == 0x61)	/* UNDO */
		ret = find_flag (tree, FLAG11);

	else if (kstate & K_ALT)	/* Shortcut */
	{
		int pos, obj;
		char c;
		char ascii;

		obj = -1;
		do
		{
			obj++;
			pos = get_magx_shortcut (tree, obj, &c);
			if (pos != -1)
			{
				if ((scan >= 0x78) && (scan < 0x80))
					ascii = keytab->capslock[scan - 0x76];
				else
					ascii = keytab->capslock[scan];
				if (toupper (c) == ascii)
				{
					ret = obj;
					break;
				}
			}
		}
		while (!(tree[obj].ob_flags & LASTOB));
	}
	if ((tree[ret].ob_flags & HIDETREE)
	    || (tree[ret].ob_state & DISABLED))
		ret = -1;
	return ret;
}
