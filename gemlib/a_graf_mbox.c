
#include "gem.h"


short
graf_mbox (short Sw, short Sh, short Sx, short Sy, short Dx, short Dy)
{
	aes_intin[0] = Sw;
	aes_intin[1] = Sh;
	aes_intin[2] = Sx;
	aes_intin[3] = Sy;
	aes_intin[4] = Dx;
	aes_intin[5] = Dy;
	
	aes_control[0] = 72;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
