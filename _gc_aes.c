#include "gem_aesP.h"

#ifdef __GNUC__
void aes(AESPB *pb)
{
	register long d1 __asm__("d1") = (long)pb;

	__asm__ __volatile__ (
		"\tmove.w	#200,%%d0\n"
		"\ttrap	#2\n"
		:
		: "r"(d1)
		: "d0", "d2", "a0", "a1", "a2", "memory", "cc"
	);
}
#endif
