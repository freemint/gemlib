#include "gem_aesP.h"


short
form_center (OBJECT *Tree, short *Cx, short *Cy, short *Cw, short *Ch)
{
	aes_addrin[0] = (long)Tree;
	
	AES_TRAP (aes_params, 54, 0,5,1,0);
	
	*Cx = aes_intout[1];
	*Cy = aes_intout[2];
	*Cw = aes_intout[3];
	*Ch = aes_intout[4];
	
	return aes_intout[0];
}
