/*
 *  $Id$
 */

#include "gem_aesP.h"

/** relinquishes program control to the operating system until
 *  a valid keypress is available in the applications' message pipe.
 *
 *  @param global_aes global AES array
 *
 *  @return 16-bit value containing the ASCII
 *          code of the key entered in the lower eight bits and the
 *          scan code in the upper 8-bits.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  TOS versions released at or above 2.06 and 3.06 disabled
 *  reception of keys 1 through 9 on the numeric keypad when
 *  used in conjunction with the alternate key. Users may now
 *  enter the full range of ASCII values by holding down alt,
 *  typing in the decimal ASCII code, and then releasing the
 *  alt key. These keys, therefore, should not be used by
 *  applications. The standard numeric keypad is still
 *  available.
 *
 *  @note The return value of this funtion is often
 *        named \p kreturn if it is used in the other mt_evnt
 *        functions.
 *
 */

short
mt_evnt_keybd(short *global_aes)
{
	AES_PARAMS(20,0,1,0,0);

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef evnt_keybd
#undef evnt_keybd
#endif
int evnt_keybd(void)
{
	return(mt_evnt_keybd(aes_global));
}
