/*
 *  $Id$
 */

#ifndef _GEM_AES_P_
# define _GEM_AES_P_

# ifndef _GEMLIB_H_
#  include "mt_gem.h"
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


#define AES_PARAMS(a,b,c,d,e) \
	static short    aes_control[AES_CTRLMAX]={a,b,c,d,e}; \
	short			aes_intin[AES_INTINMAX],			  \
					aes_intout[AES_INTOUTMAX];			  \
	long			aes_addrin[AES_ADDRINMAX],			  \
					aes_addrout[AES_ADDROUTMAX];		  \
 														  \
	AESPB aes_params;									  \
  	aes_params.control = &aes_control[0];				  \
  	aes_params.global  = &global_aes[0];				  \
  	aes_params.intin   = &aes_intin[0]; 				  \
  	aes_params.intout  = &aes_intout[0];				  \
  	aes_params.addrin  = &aes_addrin[0];				  \
  	aes_params.addrout = &aes_addrout[0]


#endif /* _GEM_AES_P_ */
