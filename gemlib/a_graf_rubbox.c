
#include "gem.h"


int
graf_rubbbox (int Ix, int Iy, int Iw, int Ih, int *Fw, int *Fh)
{
	aes_intin[0] = Ix;
	aes_intin[1] = Iy;
	aes_intin[2] = Iw;
	aes_intin[3] = Ih;
	aes_control[0] = 70;
	aes_control[1] = 4;
	aes_control[2] = 3;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	*Fw = aes_intout[1];
	*Fh = aes_intout[2];
	return aes_intout[0];
}
