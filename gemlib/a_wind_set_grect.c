#include "gem_aesP.h"


short
wind_set_grect (short WindowHandle, short What, const GRECT * r)
{
	aes_intin[0]            = WindowHandle;
	aes_intin[1]            = What;
	*(GRECT*)(aes_intin +2) = *r;
	
	AES_TRAP (aes_params, 105, 6,1,0,0);
	
	return aes_intout[0];
}
