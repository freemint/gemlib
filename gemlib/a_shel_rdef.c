#include "gem_aesP.h"


short
shel_rdef (char *lpcmd, char *lpdir)
{
	aes_addrin[0] = (long)lpcmd;
	aes_addrin[1] = (long)lpdir;
	
	AES_TRAP (aes_params, 126, 0,1,2,0);
	
	return aes_intout[0];
}
