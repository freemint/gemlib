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
 * vdi.c
 * Hilfs-Routinen rund um das VDI.
 */

#include "intern.h"


/*
 * Point-H”he zu einer Pixel-H”he ermitteln.
 */
short
height2pts (short handle, short f_id, short f_height)
{
	short d, w, h, asked, got, width, height;
	short pt = -1;
	
	vst_font (handle, f_id);
	vst_height (handle, f_height, &d, &height, &width, &d);

	asked = 99; 
	got = asked;
	while (got <= asked)
	{
		/*
		 * Schleife, solange ein kleinerer Font eingestellt werden kann;
		 * Abbruch, wenn vst_point() einen /gr”žeren/ Font als angefordert
		 * einstellt (und somit auch als tats„chliche Gr”že zurckliefert)
		 */
		asked = got - 1; 	/* 1 kleiner als aktuelle Gr”že einstellen */
		got = vst_point (handle, asked, &d, &h, &w, &d);
		if ((h == height) && (w == width))
		{
			pt = got; 		/* Punktgr”že gefunden */
			break;
		}
	}

	return pt;
}
