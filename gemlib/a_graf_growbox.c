
#include "gem.h"


int
graf_growbox (int Sx, int Sy, int Sw, int Sh, int Fx, int Fy, int Fw, int Fh)
{
	aes_intin[0] = Sx;
	aes_intin[1] = Sy;
	aes_intin[2] = Sw;
	aes_intin[3] = Sh;
	aes_intin[4] = Fx;
	aes_intin[5] = Fy;
	aes_intin[6] = Fw;
	aes_intin[7] = Fh;
	aes_control[0] = 73;
	aes_control[1] = 8;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
