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
	AES_PARAMS({129,2,1,1,0});
                   
	aes_intin[0]  = ap_cid;
	aes_intin[1]  = ap_cwhat;
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
