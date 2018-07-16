/*
 *  $Id$
 */

#include "gem_aesP.h"

/** see mt_objc_draw()
 *
 *  @param tree   see mt_objc_draw()
 *  @param start  see mt_objc_draw()
 *  @param depth  see mt_objc_draw()
 *  @param r  clipping rectangle to enforce during drawing
 *  @param global_aes global AES array
 *
 *  @return  see mt_objc_draw()
 *
 *  @since  see mt_objc_draw()
 *
 *
 */

short 
mt_objc_draw_grect(OBJECT *tree, short start, short depth, const GRECT *r, short *global_aes)
{
	AES_PARAMS(42,6,1,1,0);
                    
	aes_intin[0] = start;
	aes_intin[1] = depth;
	*(GRECT*)(aes_intin+2) = *r;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
