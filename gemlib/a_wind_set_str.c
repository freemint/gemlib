#include "gem_aesP.h"


short
wind_set_str (short WindowHandle, short What, const char *str)
{
	aes_intin[0]                  = WindowHandle;
	aes_intin[1]                  = What;
	*(const char**)(aes_intin +2) = str;
	
	AES_TRAP (aes_params, 105, 6,1,0,0);
	
	return aes_intout[0];
}
