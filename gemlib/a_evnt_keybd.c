
#include "gem.h"


int
evnt_keybd (void)
{
	aes_control[0] = 20;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
