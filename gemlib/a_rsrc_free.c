#include "gem_aesP.h"


short
rsrc_free (void)
{
	AES_TRAP (aes_params, 111, 0,1,0,0);
	
	return aes_intout[0];
}
