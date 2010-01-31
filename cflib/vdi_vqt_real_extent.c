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


#if  !defined (_GEMLIB_H_)

/*
 * Kennt die Pure/GEM-Lib nicht.
 */

void
vqt_real_extent (short handle, short x, short y, char *string, short extent[])
{
	static VDIPB vdipb =
	{
		_VDIParBlk.contrl,
		_VDIParBlk.intin,
		_VDIParBlk.ptsin,
		_VDIParBlk.intout,
		_VDIParBlk.ptsout
	};

	short i;

	i = vdi_str2array(string, _VDIParBlk.intin);

	_VDIParBlk.ptsin[0] = x;
	_VDIParBlk.ptsin[1] = y;
	_VDIParBlk.contrl[0] = 240;
	_VDIParBlk.contrl[1] = 1;
	_VDIParBlk.contrl[3] = i;
	_VDIParBlk.contrl[6] = handle;

	vdi(&vdipb);

	for (i = 0; i<8; i++)
		extent[i] = _VDIParBlk.ptsout[i];
}

#endif
