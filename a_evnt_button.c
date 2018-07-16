/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases control to the operating system until the specified mouse
 *  button event has occurred.
 *
 *  @param clicks specifies the number of mouse-clicks that must occur
 *             before returning
 *  @param mask specifies the mouse buttons to wait for as follows:
 *               - \p #LEFT_BUTTON   (0x01)  Left mouse button
 *               - \p #RIGHT_BUTTON  (0x02)  Right mouse button
 *               - \p #MIDDLE_BUTTON (0x04)  Middle button (this button would be
 *                                            the first button to the left of the
 *                                            rightmost button on the device).
 *               - \p (unamed) (0x08)  Other buttons (0x08 is the mask for
 *                                            the button to the immediate left of
 *                                            the middle button. Masks continue
 *                                            leftwards).
 *  @param state specifies the button state that must occur before
 *             returning as follows:
 *             - 0x00   All buttons released
 *             - 0x01   Left button depressed
 *             - 0x02   Right button depressed
 *             - 0x04   Middle button depressed
 *             - 0x08   etc...
 *  @param mx is a pointer to a WORD which upon return will contain the
 *             x-position of the mouse pointer at the time of the event. \n
 *             [option CHECK_NULLPTR] \a mx may be NULL
 *  @param my is a pointer to a WORD which upon return will contain the
 *             y-position of the mouse pointer at the time of the event. \n
 *             [option CHECK_NULLPTR] \a my may be NULL
 *  @param mbutton is a pointer to a WORD which upon return will
 *             contain the mouse button state as defined in state. \n
 *             [option CHECK_NULLPTR] \a mbutton may be NULL
 *  @param kmeta is a pointer to a WORD which upon return will
 *             contain the current status of the keyboard shift keys.
 *             The value is a bit-mask defined as follows:
 *             - \p #K_RSHIFT         (0x01)     Right Shift
 *             - \p #K_LSHIFT         (0x02)     Left Shift
 *             - \p #K_CTRL           (0x04)     Control
 *             - \p #K_ALT            (0x08)     Alternate
 *             .
 *             [option CHECK_NULLPTR] \a kmeta may be NULL
 *  @param global_aes global AES array
 *
 *  @return a WORD indicating the number of times the mouse
 *          button state matched state.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi(), Kbshift(), vq_mouse()
 *
 *  A previously undocumented feature of this call is accessed by
 *  logically OR'ing the clicks parameter with 0x100 or 0x200.
 *  0x100 causes the call to return when independent buttons are
 *  depressed except combination of both and 0x200 for any
 *  combination. For example, a mask value of 0x03 will return
 *  when both the left and right mouse buttons are depressed.
 *  A clicks value of 0x202 will cause the call to return when
 *  either button is depressed.
 *
 *  The values 0x103, 1, 3 are for the clicks, mask and state
 *  are the best. Other combinations may generate too many
 *  messages what could cause problems especially in
 *  multitasking operating systems.
 *
 *  This method works with mt_evnt_multi() as well.
 *
 */

short
mt_evnt_button (short clicks, short mask, short state,
				short *mx, short *my, short *mbutton, short *kmeta, short *global_aes)
{
	AES_PARAMS(21,3,5,0,0);

	aes_intin[0] = clicks;
	aes_intin[1] = mask;
	aes_intin[2] = state;

	AES_TRAP (aes_params);

#if CHECK_NULLPTR
	if (mx)
#endif
	*mx      = aes_intout[1];
#if CHECK_NULLPTR
	if (my)
#endif
	*my      = aes_intout[2];
#if CHECK_NULLPTR
	if (mbutton)
#endif
	*mbutton = aes_intout[3];
#if CHECK_NULLPTR
	if (kmeta)
#endif
	*kmeta   = aes_intout[4];

	return aes_intout[0];
}
