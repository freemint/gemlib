#include "gem_aesP.h"


short
wind_delete (short WindowHandle)
{
	aes_intin[0] = WindowHandle;
	
	AES_TRAP (aes_params, 103, 1,1,0,0);
	
	return aes_intout[0];
}
