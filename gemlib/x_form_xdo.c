/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** 
 *
 *  @param tree 
 *  @param startob 
 *  @param lastcrsr 
 *  @param tabs 
 *  @param flydial 
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 *
 *
 */

short 
mt_form_xdo(OBJECT *tree, short startob, short *lastcrsr, XDO_INF *tabs, void *flydial, short *global_aes)
{
	AES_PARAMS(50,1,2,3,0);
                    
	aes_intin[0] = startob;
	
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)tabs;
	aes_addrin[2] = (long)flydial;

	AES_TRAP(aes_params);

	*lastcrsr = aes_intout[1];
	
	return aes_intout[0];
}
