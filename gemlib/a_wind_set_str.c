#include "gem.h"


short
wind_set_str (short WindowHandle, short What, const char *str)
{
	aes_intin[0]                  = WindowHandle;
	aes_intin[1]                  = What;
	*(const char**)(aes_intin +2) = str;
	
	aes_control[0] = 105;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
