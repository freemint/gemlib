#include "gem_aesP.h"


short
shel_find (char *buf)
{
	aes_addrin[0] = (long)buf;
	
	AES_TRAP (aes_params, 124, 0,1,1,0);
	
	return aes_intout[0];
}
