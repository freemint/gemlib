#include "gem_aesP.h"


short
wind_set (short WindowHandle, short What,
          short W1, short W2, short W3, short W4)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	aes_intin[2] = W1;
	aes_intin[3] = W2;
	aes_intin[4] = W3;
	aes_intin[5] = W4;
	
	AES_TRAP (aes_params, 105, 6,1,0,0);
	
	return aes_intout[0];
}
