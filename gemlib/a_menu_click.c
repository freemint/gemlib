#include "gem_aesP.h"


short
menu_click (short click, short setit)
{
	aes_intin[0] = click;
	aes_intin[1] = setit;
	
	AES_TRAP (aes_params, 37, 2,1,0,0);
	
	return aes_intout[0];
}
