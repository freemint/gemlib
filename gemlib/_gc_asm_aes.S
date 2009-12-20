
	.globl	_aes

_aes:
	movel	sp@(4), d1		| hier kommt pb Åber den Stack!
	movew	#200, d0
#ifdef __mcoldfire__
	movel	a2, sp@-		| backup registers
	movel	d2, sp@-
#else
	moveml	d2/a2, sp@-		| backup registers
#endif
	trap	#2
#ifdef __mcoldfire__
	movel	sp@+, d2		| restore registers
	movel	sp@+, a2
#else
	moveml	sp@+, d2/a2		| restore registers
#endif
	rts
