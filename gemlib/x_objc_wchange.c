/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Alter object status and redraw object
 *
 *  @param tree as for mt_objc_change()
 *  @param obj as for mt_objc_change()
 *  @param new_state  as for mt_objc_change()
 *  @param clip NULL => whole window
 *  @param whandle window handle
 *  @param global_aes global AES array
 *
 *  @since Magic 5.10
 *
 *	This call is equivalent to mt_objc_change() without a redraw followed by
 *	mt_objc_wdraw().
 *
 */

void 
mt_objc_wchange(OBJECT *tree, short obj, short new_state, GRECT *clip, short whandle, short *global_aes)
{
	AES_PARAMS(61,3,0,2,0);

	aes_intin[0] = obj;
	aes_intin[1] = new_state;
	aes_intin[2] = whandle;

	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)clip;

	AES_TRAP(aes_params);
}
