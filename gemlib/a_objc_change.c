/*
 *  $Id$
 */

#include "gem_aesP.h"

/**  changes the display state of an object.
 *
 *  @param tree  specifies the object tree of the object to modify.
 *  @param object specifies the object to modify.
 *  @param res is reserved and should be 0.
 *  @param cx x-position of the the clipping rectangle if the
 *         object is to be redrawn.
 *  @param cy y-position of the the clipping rectangle if the
 *         object is to be redrawn.
 *  @param cw width of the the clipping rectangle if the
 *         object is to be redrawn.
 *  @param ch height of the the clipping rectangle if the
 *         object is to be redrawn.
 *  @param new_state specifies the new state of the object (same as
 *         ob_state).
 *  @param redraw may be one of the following value:
 *         - NO_DRAW (0) : the object is not redrawn
 *         - REDRAW (1) : the object is redrawn.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred and non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_draw()
 *
 */

short 
mt_objc_change(OBJECT *tree, short object, short res, short cx, short cy,
               short cw, short ch,  short new_state, short redraw, short *global_aes)
{
	AES_PARAMS(47,8,1,1,0);
                    
	aes_intin[0] = object;
	aes_intin[1] = res;
	aes_intin[2] = cx;
	aes_intin[3] = cy;
	aes_intin[4] = cw;
	aes_intin[5] = ch;
	aes_intin[6] = new_state;
	aes_intin[7] = redraw;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
