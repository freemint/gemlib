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
objc_find(void *tree, short start, short depth, short mx, short my)
{
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = start;
	gem_array->int_in[1] = depth;
	gem_array->int_in[2] = mx;
	gem_array->int_in[3] = my;
	gem_array->addr_in[0] = (long)tree;

	return call_aes(gem_array, 43);
}

/* EOF */
