#include "gem_aesP.h"


short
scrp_read (char *Scrappath)
{
	aes_addrin[0] = (long)Scrappath;
	
	AES_TRAP (aes_params, 80, 0,1,1,0);
	
	return aes_intout[0];
}
