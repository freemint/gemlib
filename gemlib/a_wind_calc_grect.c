#include "gem.h"


short
wind_calc_grect (short Type, short Parts, const GRECT *In, GRECT *Out)
{
	aes_intin[0]            = Type;
	aes_intin[1]            = Parts;
	*(GRECT*)(aes_intin +2) = *In;
	
	aes_control[0] = 108;
	aes_control[1] = 6;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*Out = *(GRECT*)(aes_intout +1);
	
	return aes_intout[0];
}
