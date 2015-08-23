/*
 *  $Id$
 */

#ifndef _GEM_AES_P_
# define _GEM_AES_P_

# ifndef _GEMLIB_H_
#  include "mt_gem.h"
# endif


#if defined(__GNUC__) && !defined(__NO_INLINE__)

static inline void
_aes_trap (AESPB * aespb)
{
	__asm__ volatile (
		"move.l	%0,d1\n\t"	/* &aespb */
		"move.w	#200,d0\n\t"
		"trap	#2"
		:
		: "g"(aespb)
		: "d0","d1","d2","a0","a1","a2","memory"
	);
}
#define AES_TRAP(aespb) _aes_trap(&aespb)

#else

#if defined(__VBCC__)

__regsused("d0/d1/a0/a1") void _aes_trap(__reg("d1")AESPB *) =
  "\tmove.l\td2,-(sp)\n"
  "\tmove.l\ta2,-(sp)\n"
  "\tmove.w\t#200,d0\n"
  "\ttrap\t#2\n"
  "\tmove.l\t(sp)+,a2\n"
  "\tmove.l\t(sp)+,d2";
#define AES_TRAP(aespb) _aes_trap(&aespb)

#else /* no usage of inlines, go the old way */

#define AES_TRAP(aespb) aes(&aespb)

#endif /* __VBCC__ */
#endif


#define AES_PARAMS(a,b,c,d,e) \
	static short    aes_control[AES_CTRLMAX]={a,b,c,d,e}; \
	short			aes_intin[AES_INTINMAX];			  \
	short			aes_intout[AES_INTOUTMAX];			  \
	long			aes_addrin[AES_ADDRINMAX];			  \
	long			aes_addrout[AES_ADDROUTMAX];		  \
 														  \
	AESPB aes_params;									  \
  	aes_params.control = &aes_control[0];				  \
  	aes_params.global  = &global_aes[0];				  \
  	aes_params.intin   = &aes_intin[0]; 				  \
  	aes_params.intout  = &aes_intout[0];				  \
  	aes_params.addrin  = &aes_addrin[0];				  \
  	aes_params.addrout = &aes_addrout[0]


#endif /* _GEM_AES_P_ */


/* special feature for AES bindings: pointer in parameters (for return values)
 * could be NULL (nice idea by Martin Elsasser against dummy variables) 
 */
#define CHECK_NULLPTR 1
