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
form_dial(short flag, short dix, short diy, short diw, short dih, \
		short cx, short cy, short cw, short ch)
{
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = flag;
	gem_array->int_in[1] = dix;
	gem_array->int_in[2] = diy;
	gem_array->int_in[3] = diw;
	gem_array->int_in[4] = dih;
	gem_array->int_in[5] = cx;
	gem_array->int_in[6] = cy;
	gem_array->int_in[7] = cw;
	gem_array->int_in[8] = ch;

	return (long)call_aes(gem_array, 51);
}

/* EOF */
