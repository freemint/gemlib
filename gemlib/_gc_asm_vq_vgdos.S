
	.globl	_vq_vgdos

_vq_vgdos:
	moveq	#-2,d0
	trap    #2
	rts
