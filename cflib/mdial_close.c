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
#include "mdial.h"


void
close_mdial (MDIAL *dial)
{
	if (dial != NULL)
	{
		if (dial->win_handle > 0)
		{
			short msg[8], d, event = 0;

			wind_close (dial->win_handle);
			wind_delete (dial->win_handle);

			/*
			 * Alle auflaufenden Redraw-Messages abarbeiten, damit
			 * alle Fenster sauber sind, wenn der Dialog beendet ist.
			 */
			while (event != MU_TIMER)
			{
				event =
					evnt_multi (MU_MESAG | MU_TIMER, 1, 1,
						    1, 0, 0, 0, 0, 0, 0, 0, 0,
						    0, 0, msg, 1, &d, &d, &d,
						    &d, &d, &d);
				if ((event & MU_MESAG)
				    && (msg[0] == WM_REDRAW))
					handle_mdial_msg (msg);
			}

			/* Men wieder an */
			enable_menu ();
		}

		/* Dialog wieder herstellen */
		dial->tree[0].ob_spec.obspec.framesize = dial->save_frame;
		set_flag (dial->tree, 1, OF_HIDETREE, FALSE);
		dial->tree[0].ob_y += dial->delta_y;

		__mdial_md_list = dial->next;
		Mfree (dial);
	}
}
