#include "gem_aesP.h"


short
menu_istart (short me_flag, OBJECT * me_tree, short me_imenu, short me_item)
{
	aes_intin[0]  = me_flag;
	aes_intin[1]  = me_imenu;
	aes_intin[2]  = me_item;
	aes_addrin[0] = (long)me_tree;
	
	AES_TRAP (aes_params, 38, 3,1,1,0);
	
	return aes_intout[0];
}
