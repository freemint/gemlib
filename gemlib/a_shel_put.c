
#include "gem.h"


int
shel_put (const char *Buf, int Len)
{
	aes_intin[0] = Len;
	aes_addrin[0] = (long) Buf;
	aes_control[0] = 123;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
