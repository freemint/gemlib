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

/* PC GEM. Warning: the same opcode as menu_attach()! */

long
menu_click(short click, short setit)
{
	GEM_ARRAY *gem_array = gem_control();

	gem_array->control[1] = 2;
	gem_array->control[2] = 1;
	gem_array->control[3] = 0;
	gem_array->control[4] = 0;

	gem_array->int_in[0] = click;
	gem_array->int_in[1] = setit;

	/* See menu_unregister() */
	return (long)call_aes(gem_array, 37+512);
}

/* EOF */
