/*
 *  $Id$
 */
 
#include "gem_aesP.h"

/** Application Control
 *
 *  @param ap_cid add parameter description here
 *  @param ap_cwhat add parameter description here
 *  @param ap_cout add parameter description here
 *  @param global_aes global AES array
 *  @return add return description here
 *
 *  add detailled description here.  
 */

short
mt_appl_control(short ap_cid, short ap_cwhat, void *ap_cout, short *global_aes)
{
   	static short 	aes_control[AES_CTRLMAX]={129,2,1,1,0};
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
                   
	aes_intin[0] = ap_cid;
	aes_intin[1] = ap_cwhat;
	aes_addrin[0] = (long)ap_cout;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_control
#undef appl_control
#endif
short 
appl_control(short ap_cid, short ap_cwhat, void *ap_cout)
{
	return(mt_appl_control(ap_cid,ap_cwhat,ap_cout, aes_global));
}
