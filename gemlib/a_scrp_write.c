#include "gem_aesP.h"


short
scrp_write (const char *Scrappath)
{
	aes_addrin[0] = (long)Scrappath;
	
	AES_TRAP (aes_params, 81, 0,1,1,0);
	
	return aes_intout[0];
}
