
#include "gemx.h"


short
fslx_close (void *fsd)
{
	aes_addrin[0] = (long) fsd;
	aes_control[0] = 191;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
