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


#ifndef _GEMLIB_H_

/*
 * Kennt die Pure/GEM-Lib nicht.
 */
int
rc_intersect (GRECT * r1, GRECT * r2)
{
	int tx, ty, tw, th, ret;

	tx = max (r2->g_x, r1->g_x);
	tw = min (r2->g_x + r2->g_w, r1->g_x + r1->g_w) - tx;
	ret = (0 < tw);
	if (ret)
	{
		ty = max (r2->g_y, r1->g_y);
		th = min (r2->g_y + r2->g_h, r1->g_y + r1->g_h) - ty;
		ret = (0 < th);
		if (ret)
		{
			r2->g_x = tx;
			r2->g_y = ty;
			r2->g_w = tw;
			r2->g_h = th;
		}
	}
	return (ret);
}

int *
grect_to_array (GRECT * g, int *pxy)
{
	pxy[0] = g->g_x;
	pxy[1] = g->g_y;
	pxy[2] = g->g_x + g->g_w - 1;
	pxy[3] = g->g_y + g->g_h - 1;
	return pxy;
}

void
array_to_grect (int *pxy, GRECT * g)
{
	g->g_x = pxy[0];
	g->g_y = pxy[1];
	g->g_w = pxy[2] - pxy[0] + 1;
	g->g_h = pxy[3] - pxy[1] + 1;
}

#endif
