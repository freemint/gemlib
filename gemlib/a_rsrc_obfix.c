#include "gem_aesP.h"


short
rsrc_obfix (OBJECT *Tree, short Index)
{
	aes_intin[0]  = Index;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 114, 1,1,1,0);
	
	return aes_intout[0];
}
