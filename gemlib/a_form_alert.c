#include "gem_aesP.h"


short
form_alert (short DefButton, const char *Str)
{
	aes_intin[0]  = DefButton;
	aes_addrin[0] = (long)Str;
	
	AES_TRAP (aes_params, 52, 1,1,1,0);
	
	return aes_intout[0];
}
