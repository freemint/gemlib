#include "gem_aesP.h"


short
graf_shrinkbox (short Fx, short Fy, short Fw, short Fh,
                short Sx, short Sy, short Sw, short Sh)
{
	aes_intin[0] = Fx;
	aes_intin[1] = Fy;
	aes_intin[2] = Fw;
	aes_intin[3] = Fh;
	aes_intin[4] = Sx;
	aes_intin[5] = Sy;
	aes_intin[6] = Sw;
	aes_intin[7] = Sh;
	
	AES_TRAP (aes_params, 74, 8,1,0,0);
	
	return aes_intout[0];
}
