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

/* as of AES 3.40 */

long
objc_sysvar(short mode, short which, short in1, short in2, short *out1, short *out2)
{
	long r;
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = mode;
	gem_array->int_in[1] = which;
	gem_array->int_in[2] = in1;
	gem_array->int_in[3] = in2;

	r = call_aes(gem_array, 48);

	if (out1)
		*out1 = gem_array->int_out[1];
	if (out2)
		*out2 = gem_array->int_out[2];

	return r;
}

/* EOF */
