#include "gem_aesP.h"


short
fsel_exinput (char *path, char *file, short *exit_but, const char *title)
{
	aes_addrin[0] = (long)path;
	aes_addrin[1] = (long)file;
	aes_addrin[2] = (long)title;
	
	AES_TRAP (aes_params, 91, 0,2,3,0);
	
	*exit_but = aes_intout[1];
	
	return aes_intout[0];
}
