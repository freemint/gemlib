#include "gem_aesP.h"
#include "gemx.h"


short
fslx_getnxtfile (void *fsd, char *fname)
{
	aes_addrin[0] = (long) fsd;
	aes_addrin[1] = (long) fname;
	aes_control[0] = 192;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
