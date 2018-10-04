#include "gem_aesP.h"

short 
mt_objc_change_grect(OBJECT *tree, short object, short res, const GRECT *r, short new_state, short redraw, short *global_aes)
{
	AES_PARAMS(47,8,1,1,0);
                    
	aes_intin[0] = object;
	aes_intin[1] = res;
	*(GRECT*)(aes_intin+2) = *r;
	aes_intin[6] = new_state;
	aes_intin[7] = redraw;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
