/*
 *  $Id$
 */

#include "gem_aesP.h"

/** 
 *
 *  @param id 
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
mt_menu_unregister(short id, short *global_aes)
{
	AES_PARAMS(36,1,1,0,0);
                    
	aes_intin[0] = id;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
