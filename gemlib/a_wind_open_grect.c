#include "gem_aesP.h"


short
wind_open_grect (short WindowHandle, const GRECT *r)
{
	aes_intin[0]            = WindowHandle;
	*(GRECT*)(aes_intin +1) = *r;
	
	AES_TRAP (aes_params, 101, 5,1,0,0);
	
	return aes_intout[0];
}
