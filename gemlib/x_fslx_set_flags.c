
#include "gemx.h"


int
fslx_set_flags (int flags, int *oldval)
{
	aes_intin[0] = 0;
	aes_intin[1] = flags;
	aes_control[0] = 195;
	aes_control[1] = 2;
	aes_control[2] = 2;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	*oldval = aes_intout[1];
	return aes_intout[0];
}
