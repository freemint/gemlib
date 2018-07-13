/*
 *  $Id$
 */

#include "gem_aesP.h"

/** suspends the application until a valid message that the
 *  application is interested in occurs.
 *
 *  @param events is a bit mask which tells the function which events
 *               your application is interested in. You should logically
 *               'OR' any of the following values together:
 *            - #MU_KEYBD  Wait for a user keypress.
 *            - #MU_BUTTON Wait for the specified mouse button state.
 *            - #MU_M1     Wait for a mouse/rectangle event as specified.
 *            - #MU_M2     Wait for a mouse/rectangle event as specified.
 *            - #MU_MESAG  Wait for a message.
 *            - #MU_TIMER  Wait the specified amount of time.
 *
 *  @param bclicks see mt_evnt_button()
 *  @param bmask see mt_evnt_button()
 *  @param bstate see mt_evnt_button()
 *  @param m1_leave see mt_evnt_mouse()
 *  @param m1_x see mt_evnt_mouse()
 *  @param m1_y see mt_evnt_mouse()
 *  @param m1_w see mt_evnt_mouse()
 *  @param m1_h see mt_evnt_mouse()
 *  @param m2_leave see mt_evnt_mouse()
 *  @param m2_x see mt_evnt_mouse()
 *  @param m2_y see mt_evnt_mouse()
 *  @param m2_w see mt_evnt_mouse()
 *  @param m2_h see mt_evnt_mouse()
 *  @param msg see mt_evnt_mesag()
 *  @param interval see mt_evnt_timer()
 *  @param mx  see mt_evnt_button()\n
 *         [option CHECK_NULLPTR] mx may be NULL
 *  @param my  see mt_evnt_button()\n
 *         [option CHECK_NULLPTR] my may be NULL
 *  @param mbutton  see mt_evnt_button()\n
 *         [option CHECK_NULLPTR] mbutton may be NULL
 *  @param kmeta see mt_evnt_button() \n
 *         [option CHECK_NULLPTR] kmeta may be NULL
 *  @param kreturn the return value of the mt_evnt_keybd() \n
 *         [option CHECK_NULLPTR] kreturn may be NULL
 *  @param mbclicks see mt_evnt_button() \n
 *         [option CHECK_NULLPTR] mbclicks may be NULL
 *  @param global_aes global AES array
 *
 *  @return a bit mask of which events actually happened as in events.
 *          This may be one or more events and your application should
 *          be prepared to handle each.
 *
 *  @since All AES versions. Under TOS 1.0, calling this function
 *         from a desk accessory with the #MU_TIMER mask and \a interval
 *         being equal to 0 could hang the system.
 *
 *  @sa mt_evnt_button(), mt_evnt_keybd(), mt_evnt_mesag(),
 *      mt_evnt_mouse(), mt_evnt_timer()
 *
 *  This call combines the functionality of mt_evnt_button(), mt_evnt_keybd(),
 *  mt_evnt_mesag(), mt_evnt_mouse(), and mt_evnt_timer() into one call.
 *  This call is usually the cornerstone of all GEM
 *  applications that must process system events.
 *
 */

short
mt_evnt_multi (short events, short bclicks, short bmask, short bstate,
			   short m1_leave, short m1_x, short m1_y, short m1_w, short m1_h,
			   short m2_leave, short m2_x, short m2_y, short m2_w, short m2_h,
			   short msg[], unsigned long interval,
			   short *mx, short *my,
			   short *mbutton, short *kmeta, short *kreturn, short *mbclicks,
			   short *global_aes)
{
	short *ptr;

	AES_PARAMS(25,16,7,1,0);

	ptr = aes_intin;
	*(ptr ++) = events;									/* [0] */
	*(ptr ++) = bclicks;
	*(ptr ++) = bmask;
	*(ptr ++) = bstate;
	*(ptr ++) = m1_leave;
	*(ptr ++) = m1_x;
	*(ptr ++) = m1_y;
	*(ptr ++) = m1_w;
	*(ptr ++) = m1_h;
	*(ptr ++) = m2_leave;
	*(ptr ++) = m2_x;
	*(ptr ++) = m2_y;
	*(ptr ++) = m2_w;
	*(ptr ++) = m2_h;
	*(ptr ++) = interval;
	*(ptr) = interval >> 16;							/* [15] */

	aes_addrin[0] = (long)msg;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (mx) *mx = aes_intout[1];
	if (my) *my = aes_intout[2];
	if (mbutton) *mbutton = aes_intout[3];
	if (kmeta) *kmeta = aes_intout[4];
	if (kreturn) *kreturn = aes_intout[5];
	if (mbclicks) *mbclicks = aes_intout[6];
#else
	ptr = &aes_intout[1];
	*mx = *(ptr ++);									/* [1] */
	*my = *(ptr ++);									/* [2] */
	*mbutton = *(ptr ++);						    	/* [3] */
	*kmeta = *(ptr ++);								/* [4] */
	*kreturn = *(ptr ++);									/* [5] */
	*mbclicks = *(ptr);								    /* [6] */
#endif

	return (aes_intout[0]);
}
