#include "gem.h"


short
objc_order (OBJECT *Tree, short Object, short NewPos)
{
	aes_intin[0] = Object;
	aes_intin[1] = NewPos;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 45;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
