#include "gem_aesP.h"


short
wind_calc (short Type, short Parts, short InX, short InY, short InW, short InH,
           short *OutX, short *OutY, short *OutW, short *OutH)
{
	aes_intin[0] = Type;
	aes_intin[1] = Parts;
	aes_intin[2] = InX;
	aes_intin[3] = InY;
	aes_intin[4] = InW;
	aes_intin[5] = InH;
	
	AES_TRAP (aes_params, 108, 6,5,0,0);
	
	*OutX = aes_intout[1];
	*OutY = aes_intout[2];
	*OutW = aes_intout[3];
	*OutH = aes_intout[4];
	
	return aes_intout[0];
}
