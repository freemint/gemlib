
#include "gem.h"


short
menu_popup (MENU * me_menu, short me_xpos, short me_ypos, MENU * me_mdata)
{
	aes_intin[0] = me_xpos;
	aes_intin[1] = me_ypos;
	
	aes_addrin[0] = (long) me_menu;
	aes_addrin[1] = (long) me_mdata;
	
	aes_control[0] = 36;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
