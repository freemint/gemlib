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
 *  @param sflag If is \p EDC_INQUIRE (0) then \p value is ignored and the current
 *               double-click rate is returned. If is \p EDC_SET (1) then the \p value
 *               is used to set a new doble-click rate value.
 *  @param global_aes global AES array
 *
 *  @return the newly set or current double-click rate based on flag.
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

#ifdef evnt_dclick
#undef evnt_dclick
#endif
short evnt_dclick(short value, short sflag)
{
	return(mt_evnt_dclick(value, sflag, aes_global));
}
