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
wind_sget(short handle, short field, char *buff)
{
	GEM_ARRAY *gem_array = gem_control();

	gem_array->control[1] = 4;
	gem_array->control[2] = 1;
	gem_array->control[3] = 0;
	gem_array->control[4] = 0;

	gem_array->int_in[0] = handle;
	gem_array->int_in[1] = field;
	gem_array->int_in[2] = (unsigned long)buff >> 16;
	gem_array->int_in[3] = (unsigned long)buff & 0xffff;

	return call_aes(gem_array, 104+512);
}

/* EOF */
