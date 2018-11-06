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
 *  @param global_aes global AES array
 *
 *  @return 0 if the mouse button was released outside of the
 *          object or a 1 if the button was released inside of the object.
 *
 *  @since All AES versions.
 *
 *  @sa mt_form_button()
 *
 *  This call is used internally by mt_form_button() and mt_form_do()
 *  and is usually only necessary if you are replacing one of
 *  these handlers.
 *
 *  As this call returns when the mouse button is released, it
 *  should only be made when the mouse button is depressed.
 *
 */

short
mt_graf_watchbox(OBJECT *tree, short object, short in_state, short out_state, short *global_aes)
{
	AES_PARAMS(75,4,1,1,0);

	aes_addrin[0] = (long)tree;
	aes_intin[0]  = 0;
	aes_intin[1]  = object;
	aes_intin[2]  = in_state;
	aes_intin[3]  = out_state;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
