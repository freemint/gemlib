#include "gemx.h"
#include "gem_aesP.h"


void
objc_wchange (OBJECT *tree, short obj, short new_state, GRECT *clip,
	      short whandle)
{
	aes_intin[0] = obj;
	aes_intin[1] = new_state;
	aes_intin[2] = whandle;

	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) clip;

	aes_control[0] = 61;
	aes_control[1] = 3;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;

	aes (&aes_params);
}
