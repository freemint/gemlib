#include "gem_aesP.h"


short
form_do (OBJECT *Tree, short StartObj)
{
	aes_intin[0]  = StartObj;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 50, 1,1,1,0);
	
	return aes_intout[0];
}
