/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases control to the operating system until
 *  a specified amount of time has passed.
 *
 *  @param interval time value specified in milliseconds.
 *  @param global_aes global AES array
 *
 *  @return reserved and is currently always 1.
 *
 *  @since All AES versions. Under TOS 1.0, calling this
 *         function from a desk accessory with \a interval
 *         having a value of 0 will hang the system.
 *
 *  @sa mt_evnt_multi()
 *
 *  This function should not be relyed on as an accurate clock.
 *  The time specified is used as a minimum time value only and
 *  the function will return at some point after that duration
 *  has passed.
 *
 */

short
mt_evnt_timer (unsigned long interval, short *global_aes)
{
	unsigned short *i = (unsigned short *)&interval;

	AES_PARAMS(24,2,1,0,0);

	aes_intin[0] = i[1];
	aes_intin[1] = i[0];

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
