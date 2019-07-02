#include "gem_aesP.h"

/** forces an AES process switch.
 *
 *  @return none
 *
 *  @since not available in PC-GEM
 *
 *  @sa mt_appl_yield()
 *  
 */

void _appl_yield(void)
{
	__asm__ volatile (
		"move.w	#201,%%d0\n\t"
		"trap	#2"
		:
		:
		: "d0","d1","d2","a0","a1","a2","memory","cc"
	);
}
