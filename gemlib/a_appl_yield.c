/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Application Yield
 *
 *  @param global_aes global AES array
 *  @return add return description here
 *
 *  add detailled description here.  
 */

short 
mt_appl_yield(short *global_aes)
{
   	static short 	aes_control[AES_CTRLMAX]={17,0,1,0,0};
	short		    aes_intin[AES_INTINMAX],
				    aes_intout[AES_INTOUTMAX];
	long		    aes_addrin[AES_ADDRINMAX],
				    aes_addrout[AES_ADDROUTMAX];

	AESPB aes_params;
  	aes_params.control = &aes_control[0];   /* AES Control Array             */
  	aes_params.global  = &global_aes[0];    /* AES Global Array              */
  	aes_params.intin   = &aes_intin[0];     /* input integer array           */
  	aes_params.intout  = &aes_intout[0];    /* output integer array          */
  	aes_params.addrin  = &aes_addrin[0];    /* input address array           */
  	aes_params.addrout = &aes_addrout[0];   /* output address array          */
                    
	AES_TRAP(aes_params);

	return aes_intout[0]; 
}

#ifdef appl_yield
#undef appl_yield
#endif
short 
appl_yield(void)
{
	return(mt_appl_yield(aes_global));
}

