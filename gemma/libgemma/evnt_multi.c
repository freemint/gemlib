/*
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This file is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

# include "extdef.h"

long
evnt_multi(short mflags, short mbclicks, short mbmask, short mbstate, \
	short mm1flags, short mm1x, short mm1y, short mm1w, short mm1h, \
	short mm2flags, short mm2x, short mm2y, short mm2w, short mm2h, \
	short *mmgpbuff, unsigned long count, short *mmox, short *mmoy, \
	short *mmobut, short *mmokstate, short *mkreturn, short *mbreturn)
{
	long r;
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = mflags;
	gem_array->int_in[1] = mbclicks;
	gem_array->int_in[2] = mbmask;
	gem_array->int_in[3] = mbstate;
	gem_array->int_in[4] = mm1flags;
	gem_array->int_in[5] = mm1x;
	gem_array->int_in[6] = mm1y;
	gem_array->int_in[7] = mm1w;
	gem_array->int_in[8] = mm1h;
	gem_array->int_in[9] = mm2flags;
	gem_array->int_in[10] = mm2x;
	gem_array->int_in[11] = mm2y;
	gem_array->int_in[12] = mm2w;
	gem_array->int_in[13] = mm2h;
	gem_array->int_in[14] = (short)count;
	gem_array->int_in[15] = (short)(count>>16);

	gem_array->addr_in[0] = (long)mmgpbuff;

	r = call_aes(gem_array, 25);

	if (mmox)
		*mmox = gem_array->int_out[1];
	if (mmoy)
		*mmoy = gem_array->int_out[2];
	if (mmobut)
		*mmobut = gem_array->int_out[3];
	if (mmokstate)
		*mmokstate = gem_array->int_out[4];
	if (mkreturn)
		*mkreturn = gem_array->int_out[5];
	if (mbreturn)
		*mbreturn = gem_array->int_out[6];

	return r;
}

/* EOF */
