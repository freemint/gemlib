/*
 *  $Id$
 */

#include "gem_aesP.h"

/** 
 *
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
mt_scrp_clear( short *global_aes)
{
	AES_PARAMS(82,0,1,0,0);

	AES_TRAP(aes_params);

	return aes_intout[0];
}
