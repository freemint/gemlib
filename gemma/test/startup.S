| Simple startup module

|  This program is free software; you can redistribute it and/or modify
|  it under the terms of the GNU General Public License as published by
|  the Free Software Foundation; either version 2 of the License, or
|  (at your option) any later version.
|
|  This program is distributed in the hope that it will be useful,
|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|  GNU General Public License for more details.
|
|  You should have received a copy of the GNU General Public License
|  along with this program; if not, write to the Free Software
|  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "symbols.h"

	.globl	C_SYMBOL_NAME(main)
	.globl	C_SYMBOL_NAME(_base)


	.data
__dummy:	.long	0x11111918

	.data
	.comm	__stack,0x4000

	.text
	movel	%sp@(0x04),%a0	| basepage address

	lea	%pc@(__stack+0x4000-0x0040.w),%sp

	movel	%a0@(0x0018),%d0		| address of the BSS segment
	addl	%a0@(0x001c),%d0		| size of the BSS segment
	subl	%a0,%d0

	movel	%d0,%sp@-		| new size
	movel	%a0,%sp@-		| start address
	pea	0x004a0000:l		| Mshrink()
	trap	#1
	lea	%sp@(12),%sp

	bsr.w	C_SYMBOL_NAME(main)

	movew	%d0,%sp@-
	movew	#0x004c,%sp@-
	trap	#1

	.globl	C_SYMBOL_NAME(__main)

C_SYMBOL_NAME(__main):	rts

| EOF
