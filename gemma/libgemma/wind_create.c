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
wind_create(short kind, short wx, short wy, short ww, short wh)
{
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = kind;
	gem_array->int_in[1] = wx;
	gem_array->int_in[2] = wy;
	gem_array->int_in[3] = ww;
	gem_array->int_in[4] = wh;

	return call_aes(gem_array, 100);
}

/* EOF */
