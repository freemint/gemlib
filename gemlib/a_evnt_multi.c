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
 *            - \p MU_KEYBD   (0x01) Wait for a user keypress.
 *            - \p MU_BUTTON  (0x02) Wait for the specified mouse button
 *                                   state.
 *            - \p MU_M1      (0x04) Wait for a mouse/rectangle event as
 *                                   specified.
 *            - \p MU_M2      (0x08) Wait for a mouse/rectangle event as
 *                                   specified.
 *            - \p MU_MESAG   (0x10) Wait for a message.
 *            - \p MU_TIMER   (0x20) Wait the specified amount of time.
 *
 *  @param bclicks
 *  @param bmask
 *  @param bstate see mt_evnt_button()
 *  @param m1_flag
 *  @param m1_x
 *  @param m1_y
 *  @param m1_w
 *  @param m1_h see mt_evnt_mouse()
 *  @param m2_flag
 *  @param m2_x
 *  @param m2_y
 *  @param m2_w
 *  @param m2_h see mt_evnt_mouse()
 *  @param msg see mt_evnt_mesag()
 *  @param interval see mt_evnt_timer()
 *  @param mx
 *  @param my
 *  @param mbutton
 *  @param kstate see mt_evnt_button()
 *  @param key the return value of the evnt_keybd()
 *  @param mbclicks see mt_evnt_button()
 *  @param global_aes global AES array
 *
 *  @return a bit mask of which events actually happened as in events.
 *          This may be one or more events and your application should
 *          be prepared to handle each.
 *
 *  @since All AES versions. Under TOS 1.0, calling this function
 *         from a desk accessory with the MU_TIMER mask and \p interval
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
 *  The only facet of mt_evnt_multi() which has changed from AES
 *  version 4.0 is that which relates to mt_evnt_mesag(). For
 *  further information you should consult that section.
 *
 */

short
mt_evnt_multi (short events, short bclicks, short bmask, short bstate,
			   short m1_flag, short m1_x, short m1_y, short m1_w, short m1_h,
			   short m2_flag, short m2_x, short m2_y, short m2_w, short m2_h,
			   short msg[], unsigned long interval,
			   short *mx, short *my,
			   short *mbutton, short *kstate, short *key, short *mbclicks,
			   short *global_aes)
{
	short *ptr;
	unsigned short *i = (unsigned short *)&interval;

	AES_PARAMS(25,16,7,1,0);

	ptr = aes_intin;
	*(ptr ++) = events;									/* [0] */
	*(ptr ++) = bclicks;
	*(ptr ++) = bmask;
	*(ptr ++) = bstate;
	*(ptr ++) = m1_flag;
	*(ptr ++) = m1_x;
	*(ptr ++) = m1_y;
	*(ptr ++) = m1_w;
	*(ptr ++) = m1_h;
	*(ptr ++) = m2_flag;
	*(ptr ++) = m2_x;
	*(ptr ++) = m2_y;
	*(ptr ++) = m2_w;
	*(ptr ++) = m2_h;
	*(ptr ++) = i[1];
	*(ptr) = i[0];										/* [15] */

	aes_addrin[0] = (long)msg;

	aes(&aes_params);

	ptr = &aes_intout[1];
	*mx = *(ptr ++);									/* [1] */
	*my = *(ptr ++);									/* [2] */
	*mbutton = *(ptr ++);						    	/* [3] */
	*kstate = *(ptr ++);								/* [4] */
	*key = *(ptr ++);									/* [5] */
	*mbclicks = *(ptr);								    /* [6] */

	return (aes_intout[0]);
}

#ifdef evnt_multi
#undef evnt_multi
#endif
short
evnt_multi(short events, short bclicks, short bmask, short bstate,
		   short m1_flag, short m1_x, short m1_y, short m1_w, short m1_h,
		   short m2_flag, short m2_x, short m2_y, short m2_w, short m2_h,
		   short msg[], unsigned long interval,
		   short *mx, short *my,
		   short *mbutton, short *kstate, short *key, short *mbclicks)
{
	return(mt_evnt_multi(events, bclicks, bmask, bstate, m1_flag, m1_x, m1_y, m1_w, m1_h, m2_flag, m2_x, m2_y, m2_w, m2_h, msg, interval, mx, my, mbutton, kstate, key, mbclicks, aes_global));
}
