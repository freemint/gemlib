/*
 * gem_aesP.h -- AES trap interface
 *
 *    <AltF4@freemint.de>
 */

#ifndef _GEM_AES_P_
# define _GEM_AES_P_

# include "gem.h"


#if defined(__GNUC_INLINE__) && (__GNUC__ > 2 || __GNUC_MINOR__ > 5)

static inline void
_aes_trap (AESPB * aespb, long cntrl_0_1, long cntrl_2_3, short cntrl_4)
{
	__asm__ volatile ("
		movea.l %0, a0;    | &aespb
		move.l  a0, d1;
		move.l  (a0), a0;  | aespb->control
		move.l  %1, (a0)+; | cntrl_0, cntrl_1
		move.l  %2, (a0)+; | cntrl_2, cntrl_3
		move.l  %3, d0;    | 0x00C8,  cntrl_4
		move.w  d0, (a0);  | cntrl_4
		swap    d0;        | 0x00C8
		trap    #2;
		"
		:
		: "a"(aespb), "g"(cntrl_0_1), "g"(cntrl_2_3), "g"(0xC80000uL|cntrl_4)
		: "a0", "d0","d1"
	);
}
#define AES_TRAP(aespb, cntrl_0, cntrl_1, cntrl_2, cntrl_3, cntrl_4) \
	_aes_trap (&aespb, \
	           (cntrl_0##uL<<16)|cntrl_1, \
	           (cntrl_2##uL<<16)|cntrl_3, \
	            cntrl_4)


#else /* no usage of gnu inlines, go the old way */

#define AES_TRAP(aespb, cntrl_0, cntrl_1, cntrl_2, cntrl_3, cntrl_4) \
	aes_control[0] = cntrl_0; \
	aes_control[1] = cntrl_1; \
	aes_control[2] = cntrl_2; \
	aes_control[3] = cntrl_3; \
	aes_control[4] = cntrl_4; \
	aes (&aespb);

#endif


extern short aes_control[];
extern short aes_global[];
extern short aes_intin[];
extern short aes_intout[];
extern long  aes_addrin[];
extern long  aes_addrout[];


# endif /* _GEM_AES_P_ */
