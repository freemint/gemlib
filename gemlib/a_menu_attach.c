#include "gem_aesP.h"


short
menu_attach (short me_flag, OBJECT * me_tree, short me_item, MENU * me_mdata)
{
	aes_intin[0]  = me_flag;
	aes_intin[1]  = me_item;
	aes_addrin[0] = (long)me_tree;
	aes_addrin[1] = (long)me_mdata;
	
	AES_TRAP (aes_params, 37, 2,1,2,0);
	
	return aes_intout[0];
}
