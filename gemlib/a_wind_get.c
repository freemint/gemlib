#include "gem_aesP.h"


short
wind_get (short WindowHandle, short What,
          short *W1, short *W2, short *W3, short *W4)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	aes_intin[2] = *W1;  /* set always, only needed for WF_DCOLOR and WF_COLOR */
	
	AES_TRAP (aes_params, 104, 2,5,0,0);
	
	*W1 = aes_intout[1];
	*W2 = aes_intout[2];
	*W3 = aes_intout[3];
	*W4 = aes_intout[4];
	
	return aes_intout[0];
}
