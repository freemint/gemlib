/*
 *  $Id$
 */

#include "gem_aesP.h"

/** allows the user to slide a child object
 *  within the bounds of its parent. It is often used to
 *  implement slider controls.
 *
 *  @param tree is pointer to the object tree containing the child and
 *               parent objects.
 *  @param parent is the object index of an object which bounds the
 *               movement of the \p object.
 *  @param object is the object index of the
 *               object which can be moved within the bounds of parent.
 *  @param direction specifies the orientation of the allowed movement.
 *               0 is horizontal (left-right), 1 is vertical (up-down).
 *  @param global_aes global AES array
 *
 *  @return a value specifying the relative offset of the child within
 *          the parent as a number between 0 and 1000.
 *
 *  @since All AES versions.
 *
 *  @sa mt_graf_mbox()
 *
 *  This call can be used easily with sliders built into
 *  dialogs by making the slider bar a TOUCHEXIT and calling
 *  this function when it is clicked.
 *
 *  This call should only be
 *  made when the mouse button is depressed as it returns when
 *  it is released.
 *
 */

short
mt_graf_slidebox(OBJECT *tree, short parent, short object, short direction, short *global_aes)
{
	AES_PARAMS(76,3,1,1,0);

	aes_addrin[0] = (long)tree;
	aes_intin[0]  = parent;
	aes_intin[1]  = object;
	aes_intin[2]  = direction;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef graf_slidebox
#undef graf_slidebox
#endif
short
graf_slidebox(OBJECT *tree, short parent, short object, short direction)
{
	return(mt_graf_slidebox(tree, parent, object, direction, aes_global));
}
