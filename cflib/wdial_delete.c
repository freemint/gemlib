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
#include "wdial.h"


/*
 * Dialog entfernen.
 */
void
delete_wdial (WDIALOG * wd)
{
	if (wd != NULL)
	{
		WDIALOG *p;

		if (wd->win_handle > 0)
		{
			close_wdial (wd);
			wind_delete (wd->win_handle);
			wd->win_handle = -1;
		}

		/* aus Liste l”schen */
		if (wd == __wdial_list)	/* erster? */
			__wdial_list = wd->next;
		else
		{
			p = __wdial_list;
			while (p->next != NULL && p->next != wd)
				p = p->next;
			p->next = wd->next;
		}

		Mfree (wd);
	}
}
