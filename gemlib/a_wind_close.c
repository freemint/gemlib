#include "gem_aesP.h"


short
wind_close (short WindowHandle)
{
	aes_intin[0] = WindowHandle;
	
	AES_TRAP (aes_params, 102, 1,1,0,0);
	
	return aes_intout[0];
}
