#include "gem_aesP.h"


short
appl_tplay (void *Mem, short Num, short Scale)
{
	aes_intin[0]  = Num;
	aes_intin[1]  = Scale;
	aes_addrin[0] = (long)Mem;
	
	AES_TRAP (aes_params, 14, 2,1,1,0);
	
	return aes_intout[0];
}
