
#include "symbols.h"

	.globl	C_SYMBOL_NAME(aes)

C_SYMBOL_NAME(aes):
	movel	%sp@(4), %d1		| pb is passed on the stack
	movew	#200, %d0
	movel	%a2, %sp@-		| backup registers
	movel	%d2, %sp@-
	trap	#2
	movel	%sp@+, %d2		| restore registers
	movel	%sp@+, %a2
	rts
