#include "gem_aesP.h"


short
evnt_dclick (short ToSet, short SetGet)
{
	aes_intin[0] = ToSet;
	aes_intin[1] = SetGet;
	
	AES_TRAP (aes_params, 26, 2,1,0,0);
	
	return aes_intout[0];
}
