/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Application Write
 *
 *  @param ApId add parameter description here
 *  @param Length add parameter description here
 *  @param ApPbuff add parameter description here
 *  @param global_aes global AES array
 *  @return add return description here
 *
 *  add detailled description here.  
 */

short 
mt_appl_write(short ApId, short Length, void *ApPbuff, short *global_aes)
{
   	static short 	aes_control[AES_CTRLMAX]={12,2,1,1,0};
	short			aes_intin[AES_INTINMAX],
					aes_intout[AES_INTOUTMAX];
	long			aes_addrin[AES_ADDRINMAX],
					aes_addrout[AES_ADDROUTMAX];

	AESPB aes_params;
  	aes_params.control = &aes_control[0];   /* AES Control Array             */
  	aes_params.global  = &global_aes[0];    /* AES Global Array              */
  	aes_params.intin   = &aes_intin[0];     /* input integer array           */
  	aes_params.intout  = &aes_intout[0];    /* output integer array          */
  	aes_params.addrin  = &aes_addrin[0];    /* input address array           */
  	aes_params.addrout = &aes_addrout[0];   /* output address array          */

	aes_intin[0]  = ApId;
	aes_intin[1]  = Length;
	aes_addrin[0] = (long)ApPbuff;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_write
#undef appl_write
#endif
short 
appl_write(short ApId, short Length, void *ApPbuff)
{
	return(mt_appl_write( ApId, Length, ApPbuff, aes_global));
}
