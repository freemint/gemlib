/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Event Button
 *
 *  AES Opcode: 21 (0x15)
 *
 *  Releases control to the operating system until the specified mouse
 *  button event has occurred.
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
 *  This method works with evnt_multi() as well.
 *
 *  @param Clicks specifies the number of mouse-clicks that must occur
 *             before returning
 *  @param WhichButton specifies the mouse buttons to wait
 *             for as follows:
 * FIXME TODO find out the formatting for the list like the folowing...
 *             <ul>
 *               <li>
 *               \p LEFT_BUTTON      0x01     Left mouse button
 *               <li>
 *               \p RIGHT_BUTTON     0x02     Right mouse button
 *               <li>
 *               \p MIDDLE_BUTTON    0x04     Middle button (this button would be
 *                                            the first button to the left of the
 *                                            rightmost button on the device).
 *               <li>
 *               \p -                0x08     Other buttons (0x08 is the mask for
 *                                            the button to the immediate left of
 *                                            the middle button. Masks continue
 *                                            leftwards).
 *             </ul>
 *  @param WhichState specifies the button state that must occur before
 *             returning
 *  @param Mx is a pointer to a WORD which upon return will contain the
 *             x-position of the mouse pointer at the time of the event.
 *  @param My is a pointer to a WORD which upon return will contain the
 *             y-position of the mouse pointer at the time of the event.
 *  @param ButtonState is a pointer to a WORD which upon return will
 *             contain the mouse button state as defined in state.
 *  @param KeyState is a pointer to a WORD which upon return will
 *             contain the current status of the keyboard shift keys.
 *             The value is a bit-mask defined as follows:
 *
 *
 *  @param global_aes global AES array
 *  @return returns a WORD indicating the number of times the mouse
 *             button state matched state.
 *
 *  @see mt_evnt_multi(), Kbshift(), vq_mouse()
 */


short
mt_evnt_button (short Clicks, short WhichButton, short WhichState,
				short *Mx, short *My, short *ButtonState, short *KeyState, short *global_aes)
{
	AES_PARAMS({21,3,5,0,0});

	aes_intin[0] = Clicks;
	aes_intin[1] = WhichButton;
	aes_intin[2] = WhichState;

	AES_TRAP (aes_params);

	*Mx          = aes_intout[1];
	*My          = aes_intout[2];
	*ButtonState = aes_intout[3];
	*KeyState    = aes_intout[4];

	return aes_intout[0];
}

#ifdef event_button
#undef event_button
#endif
short
event_button(short Clicks, short WhichButton, short WhichState,
			 short *Mx, short *My, short *ButtonState, short *KeyState)
{
	return(mt_event_button(Clicks,WhichButton,WhichState,
						   Mx,My,ButtonState,KeyState, aes_global));
}
