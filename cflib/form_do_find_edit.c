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


short
find_edit (OBJECT *tree, short obj, short mode)
{
	short ret = 0;
	int i = 0;
	int prev = 0, next = 0;
	int first = 0, last = 0;

	do
	{
		i++;
		if (edit_valid (tree, i))
		{
			/* ersten merken */
			if (first == 0)
				first = i;

			if (i < obj)
				prev = i;
			if ((next == 0) && (i > obj))
				next = i;

			/* enth„lt beim while-Ende den letzen */
			last = i;
		}
	}
	while (!(tree[i].ob_flags & OF_LASTOB));

	if (prev == 0)
		prev = last;

	if (next == 0)
		next = first;

	switch (mode)
	{
		case FMD_FORWARD:
			ret = next;
			break;

		case FMD_BACKWARD:
			ret = prev;
			break;

		default:
			debug ("\find_edit: unbekannter Modus %d.\n", mode);
	}

	return ret;
}
