| Startup code for thread_fork()

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

	.globl	C_SYMBOL_NAME(_startup)

C_SYMBOL_NAME(_startup):
	move.l	0x04(%sp),%a0		|basepage address

	move.l	0x002c(%a0),-(%sp)	|release own environment
	move.w	#0x0049,-(%sp)
	trap	#1
	addq.l	#6,%sp

	move.l	0x04(%sp),%a0		|basepage address
	move.l	0x0010(%a0),%a1		|p_dbase

	lea	0x000c(%a0),%a2
	move.l	#256,(%a2)+		|p_tlen
	clr.l	(%a2)+			|p_dbase
	clr.l	(%a2)+			|p_dlen
	clr.l	(%a2)+			|p_bbase
	clr.l	(%a2)+			|p_blen
	
	move.l	0x0024(%a0),%a2		|p_parent
	move.l	0x2c(%a2),0x2c(%a0)	|copy the environment pointer

	move.l	0x04(%sp),-(%sp)
	move.l	#0x00000001,-(%sp)
	jsr	(%a1)
	addq.l	#0x08,%sp

	move.w	%d0,-(%sp)
	move.w	#0x004c,-(%sp)
	trap	#1

| EOF
