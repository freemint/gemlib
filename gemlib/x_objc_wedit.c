#include "gemx.h"
#include "gem_aesP.h"


short
objc_wedit (OBJECT * tree, short obj, short key, short *idx, short kind, short whandle)
{
	aes_intin[0] = obj;
	aes_intin[1] = key;
	aes_intin[2] = *idx;
	aes_intin[3] = kind;
	aes_intin[4] = whandle;
	aes_addrin[0] = (long) tree;
	aes_control[0] = 65;
	aes_control[1] = 5;
	aes_control[2] = 2;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*idx = aes_intout[1];
	return aes_intout[0];
}
