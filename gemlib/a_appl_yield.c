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
mt_appl_yield(short *global_aes)
{
	AES_PARAMS(17,0,1,0,0);
                    
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

