
#include "gem.h"


void
wind_set_str (int WindowHandle, int What, char *str)
{
	unsigned short *s = (unsigned short *) &str;

	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	aes_intin[2] = s[0];
	aes_intin[3] = s[1];
	aes_control[0] = 105;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	aes (&aes_params);
}
