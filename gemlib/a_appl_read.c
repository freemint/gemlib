
#include "gem.h"


int
appl_read (int ApId, int Length, void *ApPbuff)
{
	aes_intin[0] = ApId;
	aes_intin[1] = Length;
	aes_addrin[0] = (long) ApPbuff;
	aes_control[0] = 11;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
