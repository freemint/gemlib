#include "gem_aesP.h"


short
wind_find (short X, short Y)
{
	aes_intin[0] = X;
	aes_intin[1] = Y;
	
	AES_TRAP (aes_params, 106, 2,1,0,0);
	
	return aes_intout[0];
}
