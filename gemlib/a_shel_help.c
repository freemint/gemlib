
#include "gem.h"


short
shel_help (short sh_hmode, const char *sh_hfile, const char *sh_hkey)
{
	aes_intin[0] = sh_hmode;
	
	aes_addrin[0] = (long) sh_hfile;
	aes_addrin[1] = (long) sh_hkey;
	
	aes_control[0] = 128;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
