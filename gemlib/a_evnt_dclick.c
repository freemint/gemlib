/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Event Doubleclick
 *
 *  AES Opcode: 26 (0x1a)
 *
 *  Sets the mouse double-click response rate. This call is global, and thus,
 *  affects all applications.
 *
 *  Because this setting is global for all applications, Atari
 *  has strongly recommended that developers use this call only
 *  where appropriate (such as in a configuration CPX like the
 *  General Setup CPX included with XCONTROL).
 *
 *  @param SetGet If is \p EDC_INQUIRE (0) then \p ToSet is ignored and the current
 *               double-click rate is returned. If is \p EDC_SET (1) then the \p ToSet
 *               is used to set a new doble-click rate value.
 *  @param ToSet specifies the double-click rate as follows:
 *              <ul>
 *              <li> 0     Slowest
 *              <li> 1
 *              <li> 2
 *              <li> 3
 *              <li> 4     Fastest
 *              </ul>
 *  @param global_aes global AES array
 *
 *  @return the newly set or current double-click rate based on flag.
 */

short
mt_evnt_dclick (short ToSet, short SetGet, short *global_aes)
{
	AES_PARAMS({26,2,1,0,0});

	aes_intin[0] = ToSet;
	aes_intin[1] = SetGet;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef evnt_dclick
#undef evnt_dclick
#endif
short evnt_dclick(short ToSet, short SetGet)
{
	return(mt_evnt_dclick(ToSet, SetGet, aes_global));
}
