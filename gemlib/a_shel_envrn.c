#include "gem_aesP.h"


short
shel_envrn (char **result, const char *param)
{
	aes_addrin[0] = (long)result;
	aes_addrin[1] = (long)param;
	
	AES_TRAP (aes_params, 125, 0,1,2,0);
	
	return aes_intout[0];
}
