#include "gem_aesP.h"


short
menu_tnormal (void *Tree, short Item, short NormalFlag)
{
	aes_addrin[0] = (long) Tree;
	
	aes_intin[0] = Item;
	aes_intin[1] = NormalFlag;
	
	AES_TRAP (aes_params, 33, 2,1,1,0);
	
	return aes_intout[0];
}
