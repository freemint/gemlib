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

#include "mdial.h"


void
change_mdedit (MDIAL * md, short new)
{
	int last = 0;

	if (md != NULL)
	{
		/* 1. prfen, ob aktuelles nicht mehr gltig ist */
		if (md->edit_obj > 0)
		{
			last = -1;
			if (!edit_valid (md->tree, md->edit_obj))
			{
				objc_edit (md->tree, md->edit_obj, 0,
					   &md->edit_idx, ED_END);
				last = md->edit_obj;
			}
		}

		/*
		 * last = -1    -> aktuelles Editfeld weiterhin gltig, nix weiteres tun
		 * last = 0             -> bisher kein Editfeld, erstes suchen
		 * last > 0             -> aktuelles Editfeld ungltig geworden, n„chstes suchen
		 */
		if (last != -1)
		{
			if (new > 0 && edit_valid (md->tree, new))
				md->edit_obj = new;	/* 2a. ein gltiges neues bergeben? */
			else	/* 2b. neues suchen */
				md->edit_obj =
					find_edit (md->tree, last,
						   FMD_FORWARD);
			if (md->edit_obj > 0)
				objc_edit (md->tree, md->edit_obj, 0,
					   &md->edit_idx, ED_INIT);
		}
	}
}
