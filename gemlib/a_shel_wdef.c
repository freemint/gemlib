
#include "gem.h"


short
shel_wdef (const char *lpcmd, const char *lpdir)
{
	aes_addrin[0] = (long) lpcmd;
	aes_addrin[1] = (long) lpdir;
	
	aes_control[0] = 127;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
