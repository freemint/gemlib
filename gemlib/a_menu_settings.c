/*
 *  $Id$
 */

#include "gem_aesP.h"

/** changes the global settings for popup and
 *  scrollable menus
 *
 *  @param me_flag is one of the following value:
 *         - #MN_INQUIRE (0) : current settings are read into
 *           the MN_SET structure pointed to by \a me_values.
 *         - #MN_CHANGE (1) : current settings are set from the MN_SET
 *           structure pointed to by \a me_values.
 *  @param me_values see above
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since This function is only available with AES versions 3.30 and
 *         above.
 *
 *  The defaults set by mt_menu_settings() are global and not
 *  local to an application. You should therefore limit your
 *  use of this function to system applications like CPX's and
 *  so forth.
 *
 */

short
mt_menu_settings(short me_flag, MN_SET *me_values, short *global_aes)
{
	AES_PARAMS(39,1,1,1,0);
                    
	aes_intin[0] = me_flag;

	aes_addrin[0] = (long)me_values;

	AES_TRAP(aes_params);

	return aes_intout[0];
}	  
