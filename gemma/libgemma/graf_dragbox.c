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
graf_dragbox(short sw, short sh, short sx, short sy, \
		short bx, short by, short bw, short bh, \
		short *fx, short *fy)
{
	long r;
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = sw;
	gem_array->int_in[1] = sh;
	gem_array->int_in[2] = sx;
	gem_array->int_in[3] = sy;
	gem_array->int_in[4] = bx;
	gem_array->int_in[5] = by;
	gem_array->int_in[6] = bw;
	gem_array->int_in[7] = bh;

	r = call_aes(gem_array, 71);

	*fx = gem_array->int_out[1];
	*fy = gem_array->int_out[2];

	return r;
}

/* EOF */
