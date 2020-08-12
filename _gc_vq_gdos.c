#include "gem_vdiP.h"

#ifdef __GNUC__
short vq_gdos(void)
{
	register long ret __asm__("d0");

	__asm__ __volatile__ (
		"\tmoveq	#-2,%%d0\n"
		"\ttrap	#2\n"
		"\tcmp.w	#-2,%%d0\n"
		"\tsne		%%d0\n"
		"\text.w	%%d0\n"
# ifndef __MSHORT__
		"\text.l	%%d0\n"
# endif
		: "=r"(ret)
		:
		: "d1", "d2", "a0", "a1", "a2", "memory", "cc"
	);
	return ret;
}
#endif
