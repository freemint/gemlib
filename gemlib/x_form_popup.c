
#include "gemx.h"


short
form_popup (OBJECT * tree, short x, short y)
{
	aes_intin[0] = x;
	aes_intin[1] = y;
	aes_addrin[0] = (long) tree;
	aes_control[0] = 135;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
