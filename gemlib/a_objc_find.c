#include "gem_aesP.h"


short
objc_find (OBJECT *Tree, short Start, short Depth, short Mx, short My)
{
	aes_intin[0]  = Start;
	aes_intin[1]  = Depth;
	aes_intin[2]  = Mx;
	aes_intin[3]  = My;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 43, 4,1,1,0);
	
	return aes_intout[0];
}
