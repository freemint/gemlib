#include "gem.h"


short
objc_find (OBJECT *Tree, short Start, short Depth, short Mx, short My)
{
	aes_intin[0] = Start;
	aes_intin[1] = Depth;
	aes_intin[2] = Mx;
	aes_intin[3] = My;
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 43;
	aes_control[1] = 4;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
