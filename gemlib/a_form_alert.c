
#include "gem.h"


short
form_alert (short DefButton, const char *Str)
{
	aes_intin[0] = DefButton;
	
	aes_addrin[0] = (long) Str;
	
	aes_control[0] = 52;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
