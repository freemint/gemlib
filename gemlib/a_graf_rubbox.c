#include "gem_aesP.h"


short
graf_rubbbox (short Ix, short Iy, short Iw, short Ih, short *Fw, short *Fh)
{
	aes_intin[0] = Ix;
	aes_intin[1] = Iy;
	aes_intin[2] = Iw;
	aes_intin[3] = Ih;
	
	AES_TRAP (aes_params, 70, 4,3,0,0);
	
	*Fw = aes_intout[1];
	*Fh = aes_intout[2];
	
	return aes_intout[0];
}
