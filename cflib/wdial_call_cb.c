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
 * Ruft Exit-Callback auf und schliež ggf. den Dialog.
 */
void
wdial_call_cb (WDIALOG *wd)
{
	short close = TRUE;
	short obj;

	obj = wd->next_obj;
	if (wd->exit_cb != NULL)
		close = (wd->exit_cb) (wd, obj);

	if (close)
	{
		obj &= 0x7FFF;
		if (obj != WD_CLOSER)
			set_state (wd->tree, obj, OS_SELECTED, FALSE);

		close_wdial (wd);
	}
}
