/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns information about the current state
 *  of the mouse pointer, buttons, and keyboard
 *  meta keys state.
 *
 *  @param mx pointer to a short integer, which on function exit will be
 *         filled in with the current x-coordinate of the mouse pointer.\n
 *         [option CHECK_NULLPTR] \a mx may be NULL
 *  @param my pointer to a short integer, which on function exit will be
 *         filled in with the current y-coordinate of the mouse pointer.\n
 *         [option CHECK_NULLPTR] \a my may be NULL
 *  @param mbutton pointer to a short integer, which on function exit will be
 *         filled in with the current button state of the mouse as defined
 *         in mt_evnt_button(). \n
 *         [option CHECK_NULLPTR] \a mbutton may be NULL
 *  @param kmeta pointer to a short integer which upon return will
 *         contain the current status of the keyboard shift keys
 *         as defined in mt_evnt_button(). \n
 *         [option CHECK_NULLPTR] \a kmeta may be NULL
 *
 *  @param global_aes global AES array
 *
 *  @return is currently reserved and currently equals 1.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_button(), vq_mouse()
 *
 */

short
mt_graf_mkstate (short *mx, short *my, short *mbutton, short *kmeta, short *global_aes)
{
#if !(CHECK_NULLPTR)
	short *ptr;
#endif

	AES_PARAMS(79,0,5,0,0);

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (mx) 	 *mx	  = aes_intout[1];
	if (my) 	 *my	  = aes_intout[2];
	if (mbutton) *mbutton = aes_intout[3];
	if (kmeta)	 *kmeta   = aes_intout[4];
#else
	ptr = &aes_intout[1];
	*mx = *(ptr ++);									/* [1] */
	*my = *(ptr ++);									/* [2] */
	*mbutton = *(ptr ++);							    /* [3] */
	*kmeta = *(ptr);									/* [4] */
#endif

	return aes_intout[0];
}
