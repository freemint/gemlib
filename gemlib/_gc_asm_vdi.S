
	.globl	_vdi

_vdi:
	movel	sp@(4), d1
	movew	#115, d0
	trap	#2
	rts
