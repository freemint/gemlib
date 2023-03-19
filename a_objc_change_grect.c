#include "gem_aesP.h"

/** see mt_objc_change()
 *
 *  @param tree         see mt_objc_change()
 *  @param object       see mt_objc_change()
 *  @param res          see mt_objc_change()
 *  @param r            clipping rectangle to enforce during drawing
 *  @param new_state    see mt_objc_change() 
 *  @param redraw    see mt_objc_change() 
 *  @param global_aes   global AES array
 *
 *  @return  see mt_objc_change()
 *
 *  @since  see mt_objc_change()
 *
 *
 */

short 
mt_objc_change_grect(OBJECT *tree, short object, short res, const GRECT *r, short new_state, short redraw, short *global_aes)
{
	AES_PARAMS(47,8,1,1,0);
                    
	aes_intin[0] = object;
	aes_intin[1] = res;
	*(GRECT*)(aes_intin+2) = *r;
	aes_intin[6] = new_state;
	aes_intin[7] = redraw;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
