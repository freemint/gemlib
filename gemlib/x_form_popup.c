/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param tree
 *  @param x
 *  @param y
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 */

short 
mt_form_popup(OBJECT *tree, short x, short y, short *global_aes)
{
	AES_PARAMS(135,2,1,1,0);
                    
	aes_intin[0] = x;
	aes_intin[1] = y;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
