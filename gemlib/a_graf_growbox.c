#include "gem_aesP.h"


short
graf_growbox (short Sx, short Sy, short Sw, short Sh,
              short Fx, short Fy, short Fw, short Fh)
{
	aes_intin[0] = Sx;
	aes_intin[1] = Sy;
	aes_intin[2] = Sw;
	aes_intin[3] = Sh;
	aes_intin[4] = Fx;
	aes_intin[5] = Fy;
	aes_intin[6] = Fw;
	aes_intin[7] = Fh;
	
	AES_TRAP (aes_params, 73, 8,1,0,0);
	
	return aes_intout[0];
}
