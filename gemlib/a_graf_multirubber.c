/*
 *  $Id$
 */

#include "gem_aesP.h"

/** allows the user to change the size of
 *  a box outline with a fixed starting point.
 *
 *  @param bx
 *  @param by define the fixed upper-left corner of the box to
 *               stretch or shrink.
 *  @param mw
 *  @param mh specify the minimum width and height that
 *               the rectangle can be shrunk to.
 *  @param rec specify the "inside" box (??? TO BE CONFIRMED)
 *  @param rw
 *  @param rh are WORD pointers which will be filled in
 *               with the ending width and height of the box when the mouse
 *               button is released. \n
 *             [option CHECK_NULLPTR] rw and/or rh may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since NAES (???).
 *
 *  @sa mt_graf_rubberbox()
 *
 *  This function should only be entered when the user has
 *  depressed the mouse button as it returns when the mouse
 *  button is released.
 *
 *  @note This call is similar to mt_graf_rubberbox(). It's usefull when resizing
 *        a window using the SIZER widget. The \p bx, \p by, \p mw and \p mh defines
 *        the whole window, and \p rect defines the work area of the window.
 *
 */

short
mt_graf_multirubber(short bx, short by, short mw, short mh, GRECT *rec, short *rw, short *rh, short *global_aes)
{
	AES_PARAMS(70,4,3,1,0);

	aes_intin[0] = bx;
	aes_intin[1] = by;
	aes_intin[2] = mw;
	aes_intin[3] = mh;
	
	aes_addrin[0] = (long)rec;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (rw)
#endif
	*rw = aes_intout[1];
#if CHECK_NULLPTR
	if (rh)
#endif
	*rh = aes_intout[2];

	return aes_intout[0];
}
