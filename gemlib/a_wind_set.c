
#include "gem.h"


int
wind_set (int WindowHandle, int What, int W1, int W2, int W3, int W4)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;

#ifdef __MSHORT__
	aes_intin[2] = W1;
	aes_intin[3] = W2;
	aes_intin[4] = W3;
	aes_intin[5] = W4;
#else
	/* for 32 bit ints stuff the address into aes_intin[2] and [3] */
	switch (What)
	{
	case WF_NAME:
	case WF_INFO:
	case WF_NEWDESK:
	{
		unsigned short *s = (unsigned short *) &W1;

		aes_intin[2] = s[0];
		aes_intin[3] = s[1];
		if (What == WF_NEWDESK)
			aes_intin[4] = W2;
	}
		break;
	default:
		aes_intin[2] = W1;
		aes_intin[3] = W2;
		aes_intin[4] = W3;
		aes_intin[5] = W4;
	}
#endif

	aes_control[0] = 105;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
