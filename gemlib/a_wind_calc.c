
#include "gem.h"


int
wind_calc (int Type, int Parts, int InX, int InY, int InW, int InH, int *OutX,
	   int *OutY, int *OutW, int *OutH)
{
	aes_intin[0] = Type;
	aes_intin[1] = Parts;
	aes_intin[2] = InX;
	aes_intin[3] = InY;
	aes_intin[4] = InW;
	aes_intin[5] = InH;
	aes_control[0] = 108;
	aes_control[1] = 6;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	*OutX = aes_intout[1];
	*OutY = aes_intout[2];
	*OutW = aes_intout[3];
	*OutH = aes_intout[4];
	return aes_intout[0];
}
