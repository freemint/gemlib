
	.globl	_aes

_aes:
	movel	sp@(4), d1		| hier kommt pb Åber den Stack!
	movew	#200, d0
	trap	#2
	rts
