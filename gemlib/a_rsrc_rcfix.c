#include "gem_aesP.h"


short
rsrc_rcfix (void *rc_header)
{
	aes_addrin[0] = (long)rc_header;
	
	AES_TRAP (aes_params, 115, 0,1,1,0);
	
	return aes_intout[0];
}
