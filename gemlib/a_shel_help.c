#include "gem_aesP.h"


short
shel_help (short sh_hmode, const char *sh_hfile, const char *sh_hkey)
{
	aes_intin[0]  = sh_hmode;
	aes_addrin[0] = (long)sh_hfile;
	aes_addrin[1] = (long)sh_hkey;
	
	AES_TRAP (aes_params, 128, 1,1,2,0);
	
	return aes_intout[0];
}
