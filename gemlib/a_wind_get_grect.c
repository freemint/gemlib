#include "gem_aesP.h"


short
wind_get_grect (short WindowHandle, short What, GRECT *r)
{
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	
	AES_TRAP (aes_params, 104, 2,5,0,0);
	
	*r = *(GRECT*)(aes_intout +1);
	
	return aes_intout[0];
}
