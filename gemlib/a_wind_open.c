#include "gem_aesP.h"


short
wind_open (short WindowHandle, short Wx, short Wy, short Ww, short Wh)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = Wx;
	aes_intin[2] = Wy;
	aes_intin[3] = Ww;
	aes_intin[4] = Wh;
	
	AES_TRAP (aes_params, 101, 5,1,0,0);
	
	return aes_intout[0];
}
