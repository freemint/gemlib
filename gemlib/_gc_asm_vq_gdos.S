
#include "symbols.h"

	.globl	C_SYMBOL_NAME(vq_gdos)

C_SYMBOL_NAME(vq_gdos):
	moveq	#-2,%d0
#ifdef __mcoldfire__
	movel	%a2,%sp@-			| backup registers
	movel	%d2,%sp@-
#else
	moveml	%d2/%a2,%sp@-		| backup registers
#endif
	trap	#2
#ifdef __mcoldfire__
	movel	%sp@+,%d2			| restore registers
	movel	%sp@+,%a2
#else
	moveml	%sp@+,%d2/%a2		| restore registers
#endif
	cmpw	#-2,%d0
	sne	%d0
	extw	%d0
# ifndef __MSHORT__
	extl	%d0
# endif
	rts
