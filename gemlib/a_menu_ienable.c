#include "gem_aesP.h"


short
menu_ienable (void *Tree, short Item, short EnableFlag)
{
	aes_intin[0]  = Item;
	aes_intin[1]  = EnableFlag;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 32, 2,1,1,0);
	
	return aes_intout[0];
}
