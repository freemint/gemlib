
#include "gem.h"


short
evnt_mesag (short MesagBuf[])
{
	aes_addrin[0] = (long) MesagBuf;

	aes_control[0] = 23;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);

	return aes_intout[0];
}
