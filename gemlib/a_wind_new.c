
#include "gem.h"


void
wind_new (void)
{
	aes_control[0] = 109;
	aes_control[1] = 0;
	aes_control[2] = 0;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
}
