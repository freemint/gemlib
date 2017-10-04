/*
 * The header & some stuff
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
	.text

#include "symbols.h"

#define WITH_FUNCNAMES 1

	.long	0x70004afc	                    /* magic value (clr.l d0, illegal) */
	.long	_slbname	                    /* pointer to library's (file)name */
	.long	0x0100	                        /* version number */
	.long	0	                            /* flags, currently 0L */
	.long	C_SYMBOL_NAME(kernel32_init)	/* called when the library's been loaded */
	.long	C_SYMBOL_NAME(kernel32_exit)	/* called before the library is removed */
	.long	C_SYMBOL_NAME(kernel32_open)	/* called when a process opens the library */
	.long	C_SYMBOL_NAME(kernel32_close)	/* called when a process closes the library */
#if WITH_FUNCNAMES
	.long	_slh_names
#else
	.long	0	                            /* pointer to function names, optional */
#endif
	.long	0                               /* used by MetaDOS loader */
	.long	0,0,0,0,0,0,0	                /* unused, always 0L */

	.long	(slh_fend-slh_functions)/4	    /* number of functions */

slh_functions:
/*
 * create the dispatch table
 */
#define DOSFUNC(name) .long C_SYMBOL_NAME(dos_##name)
#define LIBFUNC(name) .long C_SYMBOL_NAME(dos_##name)
#define NOFUNC .long 0
#include "dosfuncs.h"
slh_fend:


#if WITH_FUNCNAMES
/*
 * create the function names
 */
#define DOSFUNC(name) name_##name##_str: .ascii "dos_"; .asciz #name
#define LIBFUNC(name) name_##name##_str: .ascii "dos_"; .asciz #name
#define NOFUNC
#include "dosfuncs.h"
	.even

/*
 * create the function name table
 */
_slh_names:
#define DOSFUNC(name) .long name_##name##_str
#define LIBFUNC(name) .long name_##name##_str
#define NOFUNC .long 0
#include "dosfuncs.h"

#endif


_slbname:	.asciz	"kernel32.slb"
