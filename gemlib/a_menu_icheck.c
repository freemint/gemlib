#include "gem_aesP.h"


short
menu_icheck (void *Tree, short Item, short CheckFlag)
{
	aes_intin[0]  = Item;
	aes_intin[1]  = CheckFlag;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 31, 2,1,1,0);
	
	return aes_intout[0];
}
