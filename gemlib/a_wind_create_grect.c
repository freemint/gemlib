#include "gem.h"


short
wind_create_grect (short Parts, const GRECT * r)
{
	aes_intin[0]            = Parts;
	*(GRECT*)(aes_intin +1) = *r;
	
	aes_control[0] = 100;
	aes_control[1] = 5;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
