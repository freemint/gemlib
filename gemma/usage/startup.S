| Simple startup module

	.globl	__base
	.globl	__init
	.globl	_main

| GNU Linker dislikes DATA sections of zero size, so have
| some magic value (this is the independence day in pl)

	.data
__dummy:
	dc.l	0x11111918

	.bss
__base:
	ds.l	1

	.text
__init:
	move.l	0x04(sp),a0		| basepage address
	move.l	a0,__base
#ifndef	BESTFIT
	move.l	0x000c(a0),d0		| size of the TEXT segment
	add.l	0x0014(a0),d0		| size of the DATA segment
	add.l	0x001c(a0),d0		| size of the BSS segment
	add.l	#0x00002100,d0		| stack + basepage
	lea	0(a0,d0.l),sp		| new stack pointer

	move.l	d0,-(sp)		| new size
	move.l	a0,-(sp)		| start address
	pea	(0x004a0000).l		| Mshrink()
	trap	#1
	lea	12(sp),sp
#endif
	jsr	_main
	move.w	d0,-(sp)
	move.w	#0x004c,-(sp)
	trap	#1

	.globl	___main

___main:
	rts
