#include "gem_aesP.h"


short
appl_write (short ApId, short Length, void *ApPbuff)
{
	aes_intin[0]  = ApId;
	aes_intin[1]  = Length;
	aes_addrin[0] = (long)ApPbuff;
	
	AES_TRAP (aes_params, 12, 2,1,1,0);
	
	return aes_intout[0];
}
