
#include "gem.h"


short
wind_find (short X, short Y)
{
	aes_intin[0] = X;
	aes_intin[1] = Y;
	
	aes_control[0] = 106;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
