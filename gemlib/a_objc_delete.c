#include "gem.h"


short
objc_delete (OBJECT *Tree, short Object)
{
	aes_addrin[0] = (long) Tree;
	aes_intin[0] = Object;
	aes_control[0] = 41;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
