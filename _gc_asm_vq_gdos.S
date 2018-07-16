
#include "symbols.h"

	.globl	C_SYMBOL_NAME(vq_gdos)

C_SYMBOL_NAME(vq_gdos):
	moveq	#-2,%d0
	movel	%a2,%sp@-			| backup registers
	movel	%d2,%sp@-
	trap	#2
	movel	%sp@+,%d2			| restore registers
	movel	%sp@+,%a2
	cmpw	#-2,%d0
	sne	%d0
	extw	%d0
# ifndef __MSHORT__
	extl	%d0
# endif
	rts
