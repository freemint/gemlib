
#include "gem.h"


int
wind_delete (int WindowHandle)
{
	aes_intin[0] = WindowHandle;
	aes_control[0] = 103;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
