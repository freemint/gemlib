
#include "gem.h"


short
menu_attach (short me_flag, OBJECT * me_tree, short me_item, MENU * me_mdata)
{
	aes_intin[0] = me_flag;
	aes_intin[1] = me_item;
	
	aes_addrin[0] = (long) me_tree;
	aes_addrin[1] = (long) me_mdata;
	
	aes_control[0] = 37;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
