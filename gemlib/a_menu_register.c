#include "gem_aesP.h"


short
menu_register (short ApId, char *MenuText)
{
	aes_intin[0]  = ApId;
	aes_addrin[0] = (long)MenuText;
	
	AES_TRAP (aes_params, 35, 1,1,1,0);
	
	return aes_intout[0];
}
