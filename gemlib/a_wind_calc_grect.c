#include "gem_aesP.h"


short
wind_calc_grect (short Type, short Parts, const GRECT *In, GRECT *Out)
{
	aes_intin[0]            = Type;
	aes_intin[1]            = Parts;
	*(GRECT*)(aes_intin +2) = *In;
	
	AES_TRAP (aes_params, 108, 6,5,0,0);
	
	*Out = *(GRECT*)(aes_intout +1);
	
	return aes_intout[0];
}
