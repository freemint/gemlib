#include "gem_aesP.h"


short
objc_offset (OBJECT *Tree, short Object, short *X, short *Y)
{
	aes_intin[0]  = Object;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 44, 1,3,1,0);
	
	*X = aes_intout[1];
	*Y = aes_intout[2];
	
	return aes_intout[0];
}
