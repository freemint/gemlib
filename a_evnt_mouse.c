#include "gem_aesP.h"

/** releases control to the operating system until
 *	the mouse enters or leaves a specified area of the screen.
 *
 *  @param flag specifies the event to wait for as follows:
 *             - #MO_ENTER   Wait for mouse to enter rectangle
 *             - #MO_LEAVE   Wait for mouse to leave rectangle
 *  @param x
 *  @param y
 *  @param w
 *  @param h    The rectangle to watch
 *
 *  @param mx
 *  @param my WORD pointers which will be filled in with the final
 *                position of the mouse. \n
 *         [option CHECK_NULLPTR] mx and my may be NULL
 *  @param mbutton is a WORD pointer which will be filled in upon
 *                return with the final state of the mouse button as defined
 *                in mt_evnt_button(). \n
 *         [option CHECK_NULLPTR] mbutton may be NULL
 *  @param kmeta is a WORD pointer which will be filled in upon
 *                return with the final state of the keyboard shift keys as
 *                defined in mt_evnt_button(). \n
 *         [option CHECK_NULLPTR] kmeta may be NULL
 *  @param global_aes global AES array
 *
 *  @return should be reserved (and should always be 1). Actually it depends
 *                on OS you are running, so it is not reserved any more.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  The mt_evnt_multi() function can be used to watch two mouse/rectangle
 *  events as opposed to one.
 *
 */

short
mt_evnt_mouse(short flag, short x, short y, short w, short h,
			  short *mx, short *my, short *mbutton, short *kmeta, short *global_aes)
{
	AES_PARAMS(22,5,5,0,0);

	aes_intin[0] = flag;
	aes_intin[1] = x;
	aes_intin[2] = y;
	aes_intin[3] = w;
	aes_intin[4] = h;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (mx)
#endif
	*mx = aes_intout[1];
#if CHECK_NULLPTR
	if (my)
#endif
	*my = aes_intout[2];
#if CHECK_NULLPTR
	if (mbutton)
#endif
	*mbutton = aes_intout[3];
#if CHECK_NULLPTR
	if (kmeta)
#endif
	*kmeta = aes_intout[4];
	return aes_intout[0];
}
