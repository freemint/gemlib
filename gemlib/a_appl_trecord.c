#include "gem_aesP.h"


short
appl_trecord (void *Mem, short Count)
{
	aes_intin[0]  = Count;
	aes_addrin[0] = (long)Mem;
	
	AES_TRAP (aes_params, 15, 1,1,1,0);
	
	return aes_intout[0];
}
