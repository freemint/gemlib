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
send_scchanged (void)
{
	static short msg[8];

	short d, i;

	/* gibts Broadcast? */
	if (((appl_xgetinfo (10, &i, &d, &d, &d)) && ((i & 0x00FF) >= 7))
	    || (gl_magx >= 0x400))
	{
		msg[0] = SC_CHANGED;	/* alle anderen Applikationen */
		msg[1] = gl_apid;
		msg[2] = 0;
		msg[3] = 0x0002;	/* Text */
		msg[4] = 0x2E54;	/* '.T' */
		msg[5] = 0x5845;	/* 'XT' */
		msg[6] = 0;
		msg[7] = 0;
		shel_write (7, 0, 0, (char *) msg, NULL);
	}
}
