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

short
call_aes(GEM_ARRAY *gemstr, short fn)
{
	SLB *g = get_gemma_p();
	long _CDECL (*exec)(SLB_HANDLE, long, long, GEM_ARRAY *, long) = (long _CDECL (*)(SLB_HANDLE, long, long, GEM_ARRAY *, long))g->exec;

	return (*exec)(g->handle, CALL_AES, SLB_NARGS(2), gemstr, fn);
}

/* EOF */
