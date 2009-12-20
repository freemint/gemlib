;
; aes/vdi interface code for gemlib (lattice c version)
;
	xdef	_aes,_vdi,_vq_gdos,_vq_vgdos
	section	code

_aes:
	move.l	4(sp),d1
	movem.l	d2/a2,-(a7)		;the lattice c aes interface saves these
	move.w	#200,d0			; although perhaps only a2 is required
	trap	#2
	movem.l	(a7)+,d2/a2
	rts

_vdi:						;we *think* the vdi doesn't clobber a2/d2
	move.l	4(sp),d1
	movem.l	d2/a2,-(a7)		;but we'll do this anyway until we've got gemlib sorted out
	move.w	#115,d0
	trap	#2
	movem.l	(a7)+,d2/a2
	rts

_vq_gdos:
	movem.l	d2/a2,-(a7)		;precautionary
	move.w	#-2,d0
	trap	#2
	cmp.w	#-2,d0
	sne		d0
	ext.w	d0
	movem.l	(a7)+,d2/a2
	rts

_vq_vgdos:
	movem.l	d2/a2,-(a7)		;precautionary
	moveq	#-2,d0
	trap	#2
	movem.l	(a7)+,d2/a2
	rts

	end
