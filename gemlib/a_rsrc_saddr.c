#include "gem_aesP.h"


short
rsrc_saddr (short Type, short Index, void *Address)
{
	aes_intin[0]  = Type;
	aes_intin[1]  = Index;
	aes_addrin[0] = (long)Address;
	
	AES_TRAP (aes_params, 113, 2,1,1,0);
	
	return aes_intout[0];
}
