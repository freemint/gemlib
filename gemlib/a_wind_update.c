#include "gem_aesP.h"


short
wind_update (short Code)
{
	aes_intin[0] = Code;
	
	AES_TRAP (aes_params, 107, 1,1,0,0);
	
	return aes_intout[0];
}
