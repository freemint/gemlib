#include "gem_aesP.h"


short
appl_getinfo (short type, short *out1, short *out2, short *out3, short *out4)
{
	aes_intin[0] = type;
	
	AES_TRAP (aes_params, 130, 1,5,0,0);
	
	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	*out3 = aes_intout[3];
	*out4 = aes_intout[4];
	
	return aes_intout[0];
}
