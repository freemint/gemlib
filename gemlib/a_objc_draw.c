#include "gem_aesP.h"


short
objc_draw (OBJECT *Tree, short Start, short Depth,
           short Cx, short Cy, short Cw, short Ch)
{
	aes_intin[0]  = Start;
	aes_intin[1]  = Depth;
	aes_intin[2]  = Cx;
	aes_intin[3]  = Cy;
	aes_intin[4]  = Cw;
	aes_intin[5]  = Ch;
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 42, 6,1,1,0);
	
	return aes_intout[0];
}
