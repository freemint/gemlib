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
#include "app.h"


short
hide_mouse_if_needed (GRECT *rect)
{
	if (!__app_hidden)
	{
		GRECT mouse;
		short mx, my, d;

		mouse.g_w = 63;
		mouse.g_h = 31;
		
		graf_mkstate (&mx, &my, &d, &d);
		mouse.g_x = mx - (mouse.g_w / 2);
		mouse.g_y = my - (mouse.g_h / 2);

		if (rc_intersect (rect, &mouse))
		{
			hide_mouse ();
			return TRUE;
		}
	}
	
	return FALSE;
}
