/*
 *  $Id$
 */

#include "gem_aesP.h"

/** 
 *
 *  @param click 
 *  @param setit 
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 *  @sa 
 *
 *
 *
 */

short
mt_menu_click(short click, short setit, short *global_aes)
{
	AES_PARAMS(37,2,1,0,0);
                    
	aes_intin[0] = click;
	aes_intin[1] = setit;

	AES_TRAP(aes_params);

	return aes_intout[0];
} 
