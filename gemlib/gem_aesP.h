/*
 *  $Id$
 */

#ifndef _GEM_AES_P_
# define _GEM_AES_P_

# ifndef _GEMLIB_H_
# include "gem.h"
# endif


#if defined(__GNUC_INLINE__) && (__GNUC__ > 2 || __GNUC_MINOR__ > 5)

static inline void
_aes_trap (AESPB * aespb)
{
	__asm__ volatile ("
		move.l %0, d1;    | &aespb
		move.w  #200,d0;
		trap    #2;
		"
		:
		: "a"(aespb)
		: "d0","d1"
	);
}
#define AES_TRAP(aespb) _aes_trap(&aespb)

#else /* no usage of gnu inlines, go the old way */

#define AES_TRAP(aespb) aes(&aespb)

#endif

#endif /* _GEM_AES_P_ */
