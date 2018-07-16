/*
 *  $Id$
 */

#include "gem_aesP.h"

/** sets the mouse double-click response rate. This call is global, and thus,
 *  affects all applications.
 *
 *  @param value specifies the double-click rate as follows:
 *               - 0     Slowest
 *               - 1
 *               - 2
 *               - 3
 *               - 4     Fastest
 *  @param sflag If \a sflag is #EDC_INQUIRE then \a value is ignored and the current
 *               double-click rate is returned. If \a sflag is #EDC_SET then the \a value
 *               is used to set a new double-click rate value.
 *  @param global_aes global AES array
 *
 *  @return the newly set or current double-click rate based on \a sflag.
 *
 *  @since All AES versions.
 *
 *  Because this setting is global for all applications, Atari
 *  has strongly recommended that developers use this call only
 *  where appropriate (such as in a configuration CPX like the
 *  General Setup CPX included with XCONTROL).
 *
 */

short
mt_evnt_dclick (short value, short sflag, short *global_aes)
{
	AES_PARAMS(26,2,1,0,0);

	aes_intin[0] = value;
	aes_intin[1] = sflag;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
