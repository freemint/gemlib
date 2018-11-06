#include "gem_aesP.h"
#include "mt_gemx.h"

/** Global system settings
 *
 *  @param flags Various flags, at present only:
 *         - SHOW8P3	(1)\n
 *			 SHOW8P3 is valid only for the display
 *			 of directories on DOS drives. It
 *			 corresponds to the switch "Show TOS
 *			 Files as '8+3'" in Magxdesk.
 *  @param oldval Previous value \n
 *             [option CHECK_NULLPTR] oldval may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0, if error \n 1, if OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fslx_xx() functions availability
 *
 *  This function is used (e.g. by MAGXDESK) in order to set the switch 
 *  "Show TOS Files as '8+3'" for the file selector as well.
 *
 */

short 
mt_fslx_set_flags(short flags, short *oldval, short *global_aes)
{
	AES_PARAMS(195,2,2,0,0);

	aes_intin[0] = 0;
	aes_intin[1] = flags;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (oldval)
#endif
	*oldval = aes_intout[1];
	
	return aes_intout[0];
}
