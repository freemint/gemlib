#include "gem.h"


short
objc_offset (OBJECT *Tree, short Object, short *X, short *Y)
{
	aes_addrin[0] = (long) Tree;
	aes_intin[0] = Object;
	aes_control[0] = 44;
	aes_control[1] = 1;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*X = aes_intout[1];
	*Y = aes_intout[2];
	return aes_intout[0];
}
