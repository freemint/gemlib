/*
 *  $Id$
 */

#include "gem_aesP.h"

/** modifies the given state of a specified
 *  object depending on whether the pointer is within the
 *  bounds of  the object or outside the bounds of the object
 *  as long as the left mouse button is held down.
 *
 *  @param tree is a pointer to the #ROOT object of the tree which
 *               contains the object you wish to watch.
 *  @param object is the object
 *               index of the object to watch.
 *  @param in_state is the ob_state (see mt_objc_change()) to apply while
 *               the mouse is inside of the bounds of the object.
 *  @param out_state is the ob_state to apply while the mouse is
 *               outside of the bounds of the object.
 *  @param whandle window handle
 *  @param global_aes global AES array
 *
 *  @return 0 if the mouse button was released outside of the
 *          object or a 1 if the button was released inside of the object.
 *
 *  @since MagiC 5.10.
 *
 *  @sa mt_graf_watchbox()
 *
 *  The function returns when the mouse button is released. The function is
 *  analog mt_graf_watchbox() with the difference, that here the window and the list
 *  of visible rectangles is used. 
 *
 */

short
mt_graf_wwatchbox(OBJECT *tree, short object, short in_state, short out_state, short whandle, short *global_aes)
{
	AES_PARAMS(62,4,1,1,0);

	aes_addrin[0] = (long)tree;
	aes_intin[0]  = object;
	aes_intin[1]  = in_state;
	aes_intin[2]  = out_state;
	aes_intin[3]  = whandle;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
