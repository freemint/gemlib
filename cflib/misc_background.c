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
#include "app.h"
#include "intern.h"


static void
cf_background (GRECT *box, MFDB *buffer, int get)
{
	MFDB screen;
	short xy[8];
	GRECT r;

	r = *box;
	if (rc_intersect (&gl_desk, &r))	/* nur sichtbaren Bereich */
	{
		screen.fd_addr = NULL;	/* Bildschirm */
		buffer->fd_w = r.g_w;
		buffer->fd_h = r.g_h;
		buffer->fd_wdwidth = (r.g_w + 15) >> 4;	/* Anzahl in intS */
		buffer->fd_stand = FALSE;
		buffer->fd_nplanes = gl_planes;
		if (get)
			buffer->fd_addr =
				cf_malloc ((long) buffer->fd_wdwidth * 2L *
					   r.g_h * gl_planes, "cf_background",
					   FALSE);

		if (buffer->fd_addr != NULL)
		{
			hide_mouse ();
			if (get)
			{
				xy[0] = r.g_x;
				xy[1] = r.g_y;
				xy[2] = r.g_x + r.g_w - 1;
				xy[3] = r.g_y + r.g_h - 1;
				xy[4] = 0;
				xy[5] = 0;
				xy[6] = r.g_w - 1;
				xy[7] = r.g_h - 1;
				vro_cpyfm (cf_vdi_handle, S_ONLY, xy, &screen,
					   buffer);
			}
			else
			{
				xy[0] = 0;
				xy[1] = 0;
				xy[2] = r.g_w - 1;
				xy[3] = r.g_h - 1;
				xy[4] = r.g_x;
				xy[5] = r.g_y;
				xy[6] = r.g_x + r.g_w - 1;
				xy[7] = r.g_y + r.g_h - 1;
				vro_cpyfm (cf_vdi_handle, S_ONLY, xy, buffer,
					   &screen);
				Mfree (buffer->fd_addr);
			}
			show_mouse ();
		}
		else
			form_dial (FMD_FINISH, r.g_x, r.g_y, r.g_w, r.g_h,
				   r.g_x, r.g_y, r.g_w, r.g_h);
	}
}

void
restore_background (GRECT *box, MFDB *buffer)
{
	cf_background (box, buffer, FALSE);
}

void
save_background (GRECT *box, MFDB *buffer)
{
	cf_background (box, buffer, TRUE);
}
