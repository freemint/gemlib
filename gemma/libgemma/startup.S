| Startup code for thread_fork()

	.globl	__startup

__startup:
	move.l	0x04(sp),a2
	move.l	0x0010(a2),a3
	move.l	0x0024(a2),a0
	lea	0x0008(a0),a0
	lea	0x0008(a2),a1
	moveq	#0x05,d0
cp:
	move.l	(a0)+,(a1)+
	dbra.w	d0,cp

	move.l	0x04(sp),-(sp)
	move.w	#0x0001,-(sp)
	jsr	(a3)
	addq.l	#0x06,sp

	move.w	d0,-(sp)
	move.w	#0x004c,-(sp)
	trap	#1
