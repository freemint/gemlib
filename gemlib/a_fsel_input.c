#include "gem_aesP.h"


short
fsel_input (char *path, char *file, short *exit_but)
{
	aes_addrin[0] = (long)path;
	aes_addrin[1] = (long)file;
	
	AES_TRAP (aes_params, 90, 0,2,2,0);
	
	*exit_but = aes_intout[1];
	
	return aes_intout[0];
}
