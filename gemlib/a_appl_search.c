/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Application Search
 *
 *  @param mode add parameter description here
 *  @param fname add parameter description here
 *  @param type add parameter description here
 *  @param ap_id add parameter description here
 *  @param global_aes global AES array
 *  @return add return description here
 *
 *  add detailled description here.  
 */

short 
mt_appl_search(short mode, char *fname, short *type, short *ap_id, short *global_aes)
{
   	static short 	aes_control[AES_CTRLMAX]={18,1,3,1,0};
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
                    
	aes_intin[0]  = mode;
	aes_addrin[0] = (long)fname;

	AES_TRAP(aes_params);

	*type  = aes_intout[1];
	*ap_id = aes_intout[2];
	
	return aes_intout[0];
}

#ifdef appl_search
#undef appl_search
#endif
short 
appl_search(short mode, char *fname, short *type, short *ap_id)
{
	return(mt_appl_search( mode, fname, type, ap_id, aes_global));
}

