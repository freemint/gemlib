#include "gem_aesP.h"


short
objc_order (OBJECT *Tree, short Object, short NewPos)
{
	aes_intin[0]  = Object;
	aes_intin[1]  = NewPos;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 45, 2,1,1,0);
	
	return aes_intout[0];
}
