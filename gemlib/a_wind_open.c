
#include "gem.h"


short
wind_open (short WindowHandle, short Wx, short Wy, short Ww, short Wh)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = Wx;
	aes_intin[2] = Wy;
	aes_intin[3] = Ww;
	aes_intin[4] = Wh;
	
	aes_control[0] = 101;
	aes_control[1] = 5;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
