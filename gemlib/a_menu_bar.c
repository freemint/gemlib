#include "gem_aesP.h"


short
menu_bar (void *Tree, short ShowFlag)
{
	aes_intin[0]  = ShowFlag;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 30, 1,1,1,0);
	
	return aes_intout[0];
}
