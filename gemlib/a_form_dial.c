#include "gem_aesP.h"


short
form_dial (short Flag, short Sx, short Sy, short Sw, short Sh,
           short Bx, short By, short Bw, short Bh)
{
	aes_intin[0] = Flag;
	aes_intin[1] = Sx;
	aes_intin[2] = Sy;
	aes_intin[3] = Sw;
	aes_intin[4] = Sh;
	aes_intin[5] = Bx;
	aes_intin[6] = By;
	aes_intin[7] = Bw;
	aes_intin[8] = Bh;
	
	AES_TRAP (aes_params, 51, 9,1,0,0);
	
	return aes_intout[0];
}
