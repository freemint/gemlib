#include "gem_aesP.h"


short
graf_dragbox (short Sw, short Sh, short Sx, short Sy,
              short Bx, short By, short Bw, short Bh, short *Fw, short *Fh)
{
	aes_intin[0] = Sw;
	aes_intin[1] = Sh;
	aes_intin[2] = Sx;
	aes_intin[3] = Sy;
	aes_intin[4] = Bx;
	aes_intin[5] = By;
	aes_intin[6] = Bw;
	aes_intin[7] = Bh;
	
	AES_TRAP (aes_params, 71, 8,3,0,0);
	
	*Fw = aes_intout[1];
	*Fh = aes_intout[2];
	
	return aes_intout[0];
}
