#include "gem_aesP.h"


short
appl_exit (void)
{
	AES_TRAP (aes_params, 19, 0,1,0,0);
	
	return aes_intout[0];
}
