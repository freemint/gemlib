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

/* as of AES 4.0 (MultiTOS 1.04) */

long
appl_getinfo(short cwhat, short *out1, short *out2, short *out3, short *out4)
{
	GEM_ARRAY *gem_array = gem_control();
	long r;

	gem_array->int_in[0] = cwhat;

	r = call_aes(gem_array, 130);

	*out1 = gem_array->int_out[1];
	*out2 = gem_array->int_out[2];
	*out3 = gem_array->int_out[3];
	*out4 = gem_array->int_out[4];

	return r;
}

/* EOF */
