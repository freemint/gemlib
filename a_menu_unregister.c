#include "gem_aesP.h"

/** remove accessory name from menu
 *
 *  @param id application ID of the accessory
 *  @param global_aes global AES array
 *
 *  @return at present unknown
 *
 *  This function allows an Accessorie to remove its name from the menu line.
 *  
 *  @since PC/GEM2 and MagiC 2.0
 *
 *  @sa mt_menu_register()
 */

short
mt_menu_unregister(short id, short *global_aes)
{
	AES_PARAMS(36,1,1,0,0);
                    
	aes_intin[0] = id;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
