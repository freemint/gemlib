#include "gem_aesP.h"


short
appl_search (short mode, char *fname, short *type, short *ap_id)
{
	aes_intin[0]  = mode;
	aes_addrin[0] = (long)fname;
	
	AES_TRAP (aes_params, 18, 1,3,1,0);
	
	*type  = aes_intout[1];
	*ap_id = aes_intout[2];
	
	return aes_intout[0];
}
