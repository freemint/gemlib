#include "gem_aesP.h"


short
rsrc_gaddr (short Type, short Index, void *Address)
{
	aes_intin[0] = Type;
	aes_intin[1] = Index;
	
	AES_TRAP (aes_params, 112, 2,1,0,1);
	
	*((void**)Address) = (void*)aes_addrout[0];
	
	return aes_intout[0];
}
