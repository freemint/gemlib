#include "gem_aesP.h"


short
form_error (short ErrorCode)
{
	aes_intin[0] = ErrorCode;
	
	AES_TRAP (aes_params, 53, 1,1,0,0);
	
	return aes_intout[0];
}
