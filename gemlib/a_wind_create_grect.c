#include "gem_aesP.h"


short
wind_create_grect (short Parts, const GRECT * r)
{
	aes_intin[0]            = Parts;
	*(GRECT*)(aes_intin +1) = *r;
	
	AES_TRAP (aes_params, 100, 5,1,0,0);
	
	return aes_intout[0];
}
