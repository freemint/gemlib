#include "gem_aesP.h"


short
objc_delete (OBJECT *Tree, short Object)
{
	aes_intin[0]  = Object;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 41, 1,1,1,0);
	
	return aes_intout[0];
}
