#include "gem_aesP.h"


short
evnt_keybd (void)
{
	AES_TRAP (aes_params, 20, 0,1,0,0);
	
	return aes_intout[0];
}
