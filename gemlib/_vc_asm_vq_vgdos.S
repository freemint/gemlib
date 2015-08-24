
	xdef	vq_vgdos

vq_vgdos:
	moveq	#-2,d0

	move.l	a2,-(sp)		| backup registers ok for coldfire and 68K
	move.l	d2,-(sp)

	trap    #2

	move.l	(sp)+,d2		| restore registers ok for coldfire and 68K
	move.l	(sp)+,a2

	rts
