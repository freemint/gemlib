
#include "symbols.h"

	.globl	C_SYMBOL_NAME(aes)

C_SYMBOL_NAME(aes):
	movel	%sp@(4), %d1		| pb is passed on the stack
	movew	#200, %d0
#ifdef __mcoldfire__
	movel	%a2, %sp@-		| backup registers
	movel	%d2, %sp@-
#else
	moveml	%d2/%a2, %sp@-		| backup registers
#endif
	trap	#2
#ifdef __mcoldfire__
	movel	%sp@+, %d2		| restore registers
	movel	%sp@+, %a2
#else
	moveml	%sp@+, %d2/%a2		| restore registers
#endif
	rts
