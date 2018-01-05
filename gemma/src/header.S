| The header & some stuff

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

	.text

	.long	0x70004afc	| magic value (clr.l d0, illegal)
	.long	_slbname	| pointer to library's (file)name
	.long	0x010b	| version number
	.long	0	| flags, currently 0L
	.long	C_SYMBOL_NAME(gemma_init)	| called when the library's been loaded
	.long	C_SYMBOL_NAME(gemma_exit)	| called before the library is removed
	.long	C_SYMBOL_NAME(gemma_open)	| called when a process opens the library
	.long	C_SYMBOL_NAME(gemma_close)	| called when a process closes the library
	.long	0	| pointer to function names, optional
	.long	0,0,0,0,0,0,0,0	| unused, always 0L

	.long	46	| number of functions

	.long	C_SYMBOL_NAME(gem_control)	| function table
	.long	C_SYMBOL_NAME(call_aes)
	.long	C_SYMBOL_NAME(windial_size)
	.long	C_SYMBOL_NAME(windial_create)
	.long	C_SYMBOL_NAME(windial_open)
	.long	C_SYMBOL_NAME(windial_formdo)
	.long	C_SYMBOL_NAME(windial_close)
	.long	C_SYMBOL_NAME(windial_delete)
	.long	C_SYMBOL_NAME(windial_center)
	.long	C_SYMBOL_NAME(_rc_intersect)

	.long	C_SYMBOL_NAME(rsrc_xload)
	.long	C_SYMBOL_NAME(rsrc_xalloc)
	.long	C_SYMBOL_NAME(rsrc_xfree)
	.long	C_SYMBOL_NAME(thread_fork)		| exec
	.long	C_SYMBOL_NAME(windial_alert)
	.long	C_SYMBOL_NAME(objc_xchange)
	.long	C_SYMBOL_NAME(rsrc_xgaddr)
	.long	C_SYMBOL_NAME(appl_open)
	.long	C_SYMBOL_NAME(windial_error)
	.long	0

	.long	C_SYMBOL_NAME(windial_link)		| link()
	.long	C_SYMBOL_NAME(env_get)
	.long	C_SYMBOL_NAME(env_eval)
	.long	C_SYMBOL_NAME(env_getargc)
	.long	C_SYMBOL_NAME(env_getargv)
	.long	C_SYMBOL_NAME(appl_top)
	.long	C_SYMBOL_NAME(windial_setjmp)
	.long	C_SYMBOL_NAME(windial_unlink)
	.long	C_SYMBOL_NAME(windial_longjmp)
	.long	C_SYMBOL_NAME(ftext_fix)

	.long	C_SYMBOL_NAME(av_dir_update)
	.long	C_SYMBOL_NAME(av_view)
	.long	C_SYMBOL_NAME(av_help)
	.long	C_SYMBOL_NAME(va_send)
	.long	C_SYMBOL_NAME(lib_control)	| hidden
	.long	C_SYMBOL_NAME(objc_xdraw)
	.long	C_SYMBOL_NAME(thread_fork)	| overlay
	.long	C_SYMBOL_NAME(menu_xpop)
	.long	C_SYMBOL_NAME(file_select)
	.long	C_SYMBOL_NAME(appl_close)

	.long	C_SYMBOL_NAME(open_url)
	.long	C_SYMBOL_NAME(proc_exec)
	.long	C_SYMBOL_NAME(get_version)
	.long	C_SYMBOL_NAME(get_users)
	.long	C_SYMBOL_NAME(windial_close_all)
	.long	C_SYMBOL_NAME(windial_delete_all)

	.long	0
	.long	0x070cffd6
	.long	C_SYMBOL_NAME(sflags)
_slbname:	.asciz	"gemma32.slb"

EINVAL	=	-25
EFAULT	=	-40

L_WB_MAGIC	=	180

WB_EXTHANDLER	=	100
WB_KEYHANDLER	=	WB_EXTHANDLER+8
WB_BUTHANDLER	=	WB_KEYHANDLER+8
WB_RC1HANDLER	=	WB_BUTHANDLER+8
WB_RC2HANDLER	=	WB_RC1HANDLER+8
WB_TIMHANDLER	=	WB_RC2HANDLER+8

WB_SCRATCH0	=	196
WB_SCRATCH1	=	WB_SCRATCH0+64
WB_SCRATCH2	=	WB_SCRATCH1+64
WB_SCRATCH3	=	WB_SCRATCH2+64
WB_SCRATCH4	=	WB_SCRATCH3+64
WB_SCRATCH5	=	WB_SCRATCH4+64

C_SYMBOL_NAME(windial_setjmp):
L_base	=	60
L_fn	=	L_base+4
L_nargs	=	L_fn+4
L_handle	=	L_nargs+4
L_vec	=	L_handle+4
L_addr	=	L_vec+4

	movem.l	%d1-%a6,-(%sp)

	move.l	L_handle(%sp),%a5
	cmp.l	#25091973,L_WB_MAGIC(%a5)
	beq.s	valid
	moveq	#EFAULT,%d0
	bra.s	exit

valid:	cmp.l	#4,L_nargs(%sp)
	bpl.s	ok
	moveq	#EINVAL,%d0
	bra.s	exit

ok:	lea	WB_EXTHANDLER(%a5),%a0
	lea	WB_SCRATCH0(%a5),%a1
	move.l	L_vec(%sp),%d0
	beq.s	set
	lea	WB_KEYHANDLER(%a5),%a0
	lea	WB_SCRATCH1(%a5),%a1
	subq.l	#1,%d0
	beq.s	set
	lea	WB_BUTHANDLER(%a5),%a0
	lea	WB_SCRATCH2(%a5),%a1
	subq.l	#1,%d0
	beq.s	set
	lea	WB_RC1HANDLER(%a5),%a0
	lea	WB_SCRATCH3(%a5),%a1
	subq.l	#1,%d0
	beq.s	set
	lea	WB_RC2HANDLER(%a5),%a0
	lea	WB_SCRATCH4(%a5),%a1
	subq.l	#1,%d0
	beq.s	set
	lea	WB_TIMHANDLER(%a5),%a0
	lea	WB_SCRATCH5(%a5),%a1
	subq.l	#1,%d0
	beq.s	set
	moveq	#EINVAL,%d0
exit:	movem.l	(%sp)+,%d1-%a6
	rts

set:	lea	60(%sp),%a2
	move.l	-(%a2),(%a1)+	| ret
	move.l	-(%a2),(%a1)+	| d1
	move.l	-(%a2),(%a1)+	| d2
	move.l	-(%a2),(%a1)+	| d3
	move.l	-(%a2),(%a1)+	| d4
	move.l	-(%a2),(%a1)+	| d5
	move.l	-(%a2),(%a1)+	| d6
	move.l	-(%a2),(%a1)+	| d7
	move.l	-(%a2),(%a1)+	| a0
	move.l	-(%a2),(%a1)+	| a1
	move.l	-(%a2),(%a1)+	| a2
	move.l	-(%a2),(%a1)+	| a3
	move.l	-(%a2),(%a1)+	| a4
	move.l	-(%a2),(%a1)+	| a5
	move.l	-(%a2),(%a1)+	| a6
	move.l	L_addr(%sp),(%a0)+
	move.l	%sp,(%a0)+
	movem.l	(%sp)+,%d1-%a6
	clr.l	%d0
	rts

C_SYMBOL_NAME(windial_longjmp):
L_base	=	4
L_fn	=	L_base+4
L_nargs	=	L_fn+4
L_handle	=	L_nargs+4
L_vec	=	L_handle+4

	move.l	L_handle(%sp),%a5

	cmp.l	#2,L_nargs(%sp)
	bpl.s	1f
	moveq	#EINVAL,%d0
	bra.s	exit2

1:	cmp.l	#25091973,L_WB_MAGIC(%a5)
	beq.s	0f
	moveq	#EFAULT,%d0
	bra.s	exit2

0:	lea	WB_EXTHANDLER(%a5),%a0
	lea	WB_SCRATCH0(%a5),%a1
	move.l	L_vec(%sp),%d0
	beq.s	set2
	lea	WB_KEYHANDLER(%a5),%a0
	lea	WB_SCRATCH1(%a5),%a1
	subq.l	#1,%d0
	beq.s	set2
	lea	WB_BUTHANDLER(%a5),%a0
	lea	WB_SCRATCH2(%a5),%a1
	subq.l	#1,%d0
	beq.s	set2
	lea	WB_RC1HANDLER(%a5),%a0
	lea	WB_SCRATCH3(%a5),%a1
	subq.l	#1,%d0
	beq.s	set2
	lea	WB_RC2HANDLER(%a5),%a0
	lea	WB_SCRATCH4(%a5),%a1
	subq.l	#1,%d0
	beq.s	set2
	lea	WB_TIMHANDLER(%a5),%a0
	lea	WB_SCRATCH5(%a5),%a1
	subq.l	#1,%d0
	beq.s	set2

	moveq	#EINVAL,%d0
exit2:	move.w	%d0,-(%sp)
	move.w	#0x004c,-(%sp)
	trap	#1

set2:	move.l	4(%a0),%sp
	lea	60(%sp),%sp

	move.l	(%a1)+,-(%sp)

	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)

	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)
	move.l	(%a1)+,-(%sp)

	movem.l	(%sp)+,%d1-%a6
	moveq	#1,%d0
	rts

| EOF
