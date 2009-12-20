
	.TEXT
	.EXPORT aes, vdi
	.EXPORT vq_gdos, vq_vgdos

aes:
	move.l	a0,d1		; pb in A0 und nicht auf Stack!
	move.w	#200,d0
	movem.l	d2/a2,-(sp)	; backup registers
	trap	#2
	movem.l	(sp)+,d2/a2	; restore registers
	rts

vdi:
	move.l	a0,d1
	moveq	#115,d0
	movem.l	d2/a2,-(sp)	; backup registers
	trap	#2
	movem.l	(sp)+,d2/a2	; restore registers
	rts

vq_gdos:
	moveq	#-2,d0
	movem.l	d2/a2,-(sp)	; backup registers
	trap	#2
	movem.l	(sp)+,d2/a2	; restore registers
	cmp.w	#-2,d0
	sne	d0
	ext.w	d0
	rts

vq_vgdos:
	moveq	#-2,d0
	movem.l	d2/a2,-(sp)	; backup registers
	trap    #2
	movem.l	(sp)+,d2/a2	; restore registers
	rts
