
#include "gem.h"


int
appl_getinfo (int type, int *out1, int *out2, int *out3, int *out4)
{
	aes_intin[0] = type;
	aes_control[0] = 130;
	aes_control[1] = 1;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	*out3 = aes_intout[3];
	*out4 = aes_intout[4];
	return aes_intout[0];
}
