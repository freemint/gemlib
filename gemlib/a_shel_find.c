
#include "gem.h"


int
shel_find (char *buf)
{
	aes_addrin[0] = (long) buf;
	aes_control[0] = 124;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
