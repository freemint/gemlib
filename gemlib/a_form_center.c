
#include "gem.h"


int
form_center (void *Tree, int *Cx, int *Cy, int *Cw, int *Ch)
{
	aes_addrin[0] = (long) Tree;
	aes_control[0] = 54;
	aes_control[1] = 0;
	aes_control[2] = 5;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*Cx = aes_intout[1];
	*Cy = aes_intout[2];
	*Cw = aes_intout[3];
	*Ch = aes_intout[4];
	return aes_intout[0];
}
