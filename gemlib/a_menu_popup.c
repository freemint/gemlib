#include "gem_aesP.h"


short
menu_popup (MENU * me_menu, short me_xpos, short me_ypos, MENU * me_mdata)
{
	aes_intin[0]  = me_xpos;
	aes_intin[1]  = me_ypos;
	aes_addrin[0] = (long)me_menu;
	aes_addrin[1] = (long)me_mdata;
	
	AES_TRAP (aes_params, 36, 2,1,2,1);
	
	return aes_intout[0];
}
