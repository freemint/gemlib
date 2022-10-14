#include "gem_vdiP.h"

#ifdef __GNUC__
long vq_vgdos(void)
{
	register long ret __asm__("d0");

	__asm__ __volatile__ (
		"\tmoveq	#-2,%d0\n"
		"\ttrap	#2\n"
		: "=r"(ret)
		:
		: "d1", "d2", "a0", "a1", "a2", "memory", "cc"
	);
	return (short)ret == -2 ? (short)ret : ret;
}
#endif
