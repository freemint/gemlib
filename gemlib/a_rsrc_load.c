#include "gem_aesP.h"


short
rsrc_load (const char *Name)
{
	aes_addrin[0] = (long)Name;
	
	AES_TRAP (aes_params, 110, 0,1,1,0);
	
	return aes_intout[0];
}
