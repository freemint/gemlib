#include "gem_aesP.h"


short
objc_add (OBJECT *Tree, short Parent, short Child)
{
	aes_intin[0]  = Parent;
	aes_intin[1]  = Child;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 40, 2,1,1,0);
	
	return aes_intout[0];
}
