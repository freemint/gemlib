/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Application Bit-Vector Set
 *
 *  @param bvdisk add parameter description here
 *  @param bvhard add parameter description here
 *  @param global_aes global AES array
 *  @return add return description here
 *
 *  add detailled description here.  
 */

short 
mt_appl_bvset(short bvdisk, short bvhard, short *global_aes)
{
	static short	aes_control[AES_CTRLMAX]={16,2,1,0,0};
	short			aes_intin  [AES_INTINMAX],
					aes_intout [AES_INTOUTMAX];
	long			aes_addrin [AES_ADDRINMAX],
					aes_addrout[AES_ADDROUTMAX];

	AESPB aes_params;
  	aes_params.control = &aes_control[0];
  	aes_params.global  = &global_aes[0]; 
  	aes_params.intin   = &aes_intin[0];  
  	aes_params.intout  = &aes_intout[0]; 
  	aes_params.addrin  = &aes_addrin[0]; 
  	aes_params.addrout = &aes_addrout[0];

	aes_intin[0] = bvdisk;
	aes_intin[1] = bvhard;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_bvset
#undef appl_bvset
#endif
short
appl_bvset(short bvdisk, short bvhard)
{
	return(mt_appl_bvset(bvdisk, bvhard, aes_global));
}
