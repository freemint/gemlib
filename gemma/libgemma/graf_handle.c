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
graf_handle(short *hwc, short *hhc, short *hwb, short *hhb)
{
	long r;
	GEM_ARRAY *gem_array = gem_control();

	r = call_aes(gem_array, 77);

	*hwc = gem_array->int_out[1];
	*hhc = gem_array->int_out[2];
	*hwb = gem_array->int_out[3];
	*hhb = gem_array->int_out[4];

	return r;
}

/* EOF */
