
#include "gem.h"


int
shel_rdef (char *lpcmd, char *lpdir)
{
	aes_addrin[0] = (long) lpcmd;
	aes_addrin[1] = (long) lpdir;
	aes_control[0] = 126;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
