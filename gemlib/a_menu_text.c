#include "gem_aesP.h"


short
menu_text (void *Tree, short Item, char *Text)
{
	aes_intin[0]  = Item;
	aes_addrin[0] = (long)Tree;
	aes_addrin[1] = (long)Text;
	
	AES_TRAP (aes_params, 34, 1,1,2,0);
	
	return aes_intout[0];
}
