#include "gem_aesP.h"


short
shel_put (const char *Buf, short Len)
{
	aes_intin[0]  = Len;
	aes_addrin[0] = (long)Buf;
	
	AES_TRAP (aes_params, 123, 1,1,1,0);
	
	return aes_intout[0];
}
