#include "gem_aesP.h"


short
objc_edit (OBJECT *Tree, short Object, short Char, short *Index, short Kind)
{
	aes_intin[0]  = Object;
	aes_intin[1]  = Char;
	aes_intin[2]  = *Index;
	aes_intin[3]  = Kind;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 46, 4,2,1,0);
	
	*Index = aes_intout[1];
	
	return aes_intout[0];
}
