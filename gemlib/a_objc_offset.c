/*
 *  $Id$
 */

#include "gem_aesP.h"

/** calculates the true screen coordinates of an object.
 *
 *  @param tree specifies the object tree 
 *  @param object is an object of \p tree.
 *  @param x will be filled with the true X screen position of \p object
 *  @param y will be filled with the true Y screen position of \p object
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_draw()
 *
 *  The ob_x and ob_y structure members of objects give an
 *  offset from their parent as opposed to true screen
 *  location. This call is used to determine a true screen
 *  coordinate.
 *
 *  The values returned by mt_objc_offset() coupled with the
 *  ob_width and ob_height members do not take into account
 *  negative borders, shadowing, or sculpturing. When redrawing
 *  an object you are responsible for using these values to and
 *  the object's state to compensate for a correct clipping
 *  rectangle.
 */

short 
mt_objc_offset(OBJECT *tree, short object, short *x, short *y, short *global_aes)
{
	AES_PARAMS(44,1,3,1,0);
                    
	aes_addrin[0] = (long)tree;
	aes_intin[0]  = object;

	AES_TRAP(aes_params);

	*x = aes_intout[1];
	*y = aes_intout[2];
	
	return aes_intout[0];
}

#ifdef objc_offset
#undef objc_offset
#endif
short 
objc_offset(OBJECT *tree, short object, short *x, short *y)
{
	return(mt_objc_offset(tree, object, x, y, aes_global));
}

