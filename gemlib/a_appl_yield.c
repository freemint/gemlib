#include "gem_aesP.h"


short
appl_yield (void)
{
	AES_TRAP (aes_params, 17, 0,1,0,0);
	
	return aes_intout[0];
}
