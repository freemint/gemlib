#include "gem_aesP.h"


short
menu_unregister (short id)
{
	aes_intin[0] = id;
	
	AES_TRAP (aes_params, 36, 1,1,0,0);
	
	return aes_intout[0];
}
