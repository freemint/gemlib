#include "gem_aesP.h"


short
scrp_clear (void)
{
	AES_TRAP (aes_params, 82, 0,1,0,0);
	
	return aes_intout[0];
}
