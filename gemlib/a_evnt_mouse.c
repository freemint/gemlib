/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases control to the operating system until
 *	the mouse enters or leaves a specified area of the screen.
 *
 *  @param flag specifies the event to wait for as follows:
 *             - \p MO_ENTER (0)   Wait for mouse to enter rectangle
 *             - \p MO_LEAVE (1)   Wait for mouse to leave rectangle
 *  @param x
 *  @param y
 *  @param w
 *  @param h    The rectangle to watch
 *
 *  @param mx
 *  @param my WORD pointers which will be filled in with the final
 *                position of the mouse.
 *  @param button is a WORD pointer which will be filled in upon
 *                return with the final state of the mouse button as defined
 *                in evnt_button().
 *  @param kstate is a WORD pointer which will be filled in upon
 *                return with the final state of the keyboard shift keys as
 *                defined in evnt_button().
 *  @param global_aes global AES array
 *
 *  @return should be reserved (and should always be 1). Actually it depends
 *                on OS you are running, so it is not reserved any more.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  The evnt_multi() function can be used to watch two mouse/rectangle
 *  events as opposed to one.
 *
 */

short
mt_evnt_mouse(short flag, short x, short y, short w, short h,
			  short *mx, short *my, short *button, short *kstate, short *global_aes)
{
	AES_PARAMS(22,5,5,0,0);

	aes_intin[0] = flag;
	aes_intin[1] = x;
	aes_intin[2] = y;
	aes_intin[3] = w;
	aes_intin[4] = h;

	AES_TRAP(aes_params);

	*mx = aes_intout[1];
	*my = aes_intout[2];
	*button = aes_intout[3];
	*kstate = aes_intout[4];
	return aes_intout[0];
}

#ifdef evnt_mouse
#undef evnt_mouse
#endif
short evnt_mouse(short flag, short x, short y, short w, short h,
				 short *mx, short *my, short *button, short *kstate)
{
	return(mt_evnt_mouse(flag, x, y, w, h, mx, my, button, kstate, aes_global));
}
