#include "gem_aesP.h"

/** calculates the true (absolute) screen coordinates of an object.
 *
 *  @param tree specifies the object tree 
 *  @param object is an object of \a tree.
 *  @param x will be filled with the absolute X screen position of \a object \n
 *         [option CHECK_NULLPTR] \a x may be NULL
 *  @param y will be filled with the absolute Y screen position of \a object \n
 *         [option CHECK_NULLPTR] \a y may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_draw()
 *
 *  The ob_x and ob_y structure members of objects give an
 *  offset from their parent as opposed to absolute screen
 *  location. This call is used to determine a absolute screen
 *  coordinate (from top left corner of the screen).
 *
 *  The values returned by mt_objc_offset() coupled with the
 *  ob_width and ob_height members do not take into account
 *  negative borders, shadowing, or sculpturing. When redrawing
 *  an object you are responsible for using these values to and
 *  the object's state to compensate for a correct clipping
 *  rectangle.
 *
 *  @note if you call the AES trap by yourself, note that some AES
 *   write to intout[3..6]!
 */

short 
mt_objc_offset(OBJECT *tree, short object, short *x, short *y, short *global_aes)
{
	AES_PARAMS(44,1,3,1,0);
                    
	aes_addrin[0] = (long)tree;
	aes_intin[0]  = object;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (x)
#endif
	*x = aes_intout[1];
#if CHECK_NULLPTR
	if (y)
#endif
	*y = aes_intout[2];
	
	return aes_intout[0];
}
