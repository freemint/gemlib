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
form_keybd(void *tree, short obj, short nobj, short thechar, short *nxobj, short *pchar)
{
	long r;
	GEM_ARRAY *gem_array = gem_control();

	gem_array->int_in[0] = obj;
	gem_array->int_in[1] = thechar;
	gem_array->int_in[2] = nobj;

	gem_array->addr_in[0] = (long)tree;

	r = (long)call_aes(gem_array, 55);

	*nxobj = gem_array->int_out[1];
	*pchar = gem_array->int_out[2];

	return r;
}

/* EOF */
