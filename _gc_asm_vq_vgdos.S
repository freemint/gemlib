
#include "symbols.h"

	.globl	C_SYMBOL_NAME(vq_vgdos)

C_SYMBOL_NAME(vq_vgdos):
	moveq	#-2,%d0
	movel	%a2,%sp@-		| backup registers
	movel	%d2,%sp@-
	trap    #2
	movel	%sp@+,%d2		| restore registers
	movel	%sp@+,%a2
	rts
