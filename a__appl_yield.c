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

#ifdef __GNUC__
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
#endif


#ifdef __VBCC__
static void _asm_appl_yield(void) =
  "\tmove.l\td2,-(sp)\n"
  "\tmove.l\ta2,-(sp)\n"
  "\tmove.w\t#201,d0\n"
  "\ttrap\t#2\n"
  "\tmove.l\t(sp)+,a2\n"
  "\tmove.l\t(sp)+,d2";

void _appl_yield(void)
{
	_asm_appl_yield();
}
#endif
