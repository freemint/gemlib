/*
 *  $Id$
 */

#include "gem_aesP.h"

/** 
 *
 *  @param bvdisk 
 *  @param bvhard 
 *  @param global_aes global AES array
 *
 *  @return
 *
 *  @since 
 *
 *  @sa 
 *  
 */

short 
mt_appl_bvset(short bvdisk, short bvhard, short *global_aes)
{
	AES_PARAMS(16,2,1,0,0);

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
