
#include "gem.h"


int
wind_get (int WindowHandle, int What, int *W1, int *W2, int *W3, int *W4)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	if (What == WF_DCOLOR || What == WF_COLOR)
		aes_intin[2] = *W1;
	aes_control[0] = 104;
	aes_control[1] = 2;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	*W1 = aes_intout[1];
	*W2 = aes_intout[2];
	*W3 = aes_intout[3];
	*W4 = aes_intout[4];
	return aes_intout[0];
}
