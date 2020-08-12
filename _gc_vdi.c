#include "gem_vdiP.h"

#ifdef __GNUC__
void vdi(VDIPB *pb)
{
	register long d1 __asm__("d1") = (long)pb;

	__asm__ __volatile__ (
		"\tmoveq	#115,%%d0\n"
		"\ttrap	#2\n"
		:
		: "r"(d1)
		: "d0", "d2", "a0", "a1", "a2", "memory", "cc"
	);
}
#endif
