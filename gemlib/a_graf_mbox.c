#include "gem_aesP.h"


short
graf_mbox (short Sw, short Sh, short Sx, short Sy, short Dx, short Dy)
{
	aes_intin[0] = Sw;
	aes_intin[1] = Sh;
	aes_intin[2] = Sx;
	aes_intin[3] = Sy;
	aes_intin[4] = Dx;
	aes_intin[5] = Dy;
	
	AES_TRAP (aes_params, 72, 6,1,0,0);
	
	return aes_intout[0];
}
