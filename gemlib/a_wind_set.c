
#include "gem.h"


short
wind_set (short WindowHandle, short What, short W1, short W2, short W3, short W4)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	
	aes_intin[2] = W1;
	aes_intin[3] = W2;
	aes_intin[4] = W3;
	aes_intin[5] = W4;
	
	aes_control[0] = 105;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
