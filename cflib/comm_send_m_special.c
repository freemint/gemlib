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
send_m_special (int mode, int app)
{
	static short msg[8];

	if (gl_magx)
	{
		int id;

		msg[0] = SM_M_SPECIAL;
		msg[1] = gl_apid;
		msg[2] = 0;
		msg[3] = 0;
		msg[4] = 0x4D41;	/* 'MA' */
		msg[5] = 0x4758;	/* 'GX' */
		msg[6] = mode;
		msg[7] = app;
		id = appl_find ("SCRENMGR");
		appl_write (id, (int) sizeof (msg), msg);
	}
}
