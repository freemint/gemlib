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
	AES_PARAMS({16,2,1,0,0});

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
