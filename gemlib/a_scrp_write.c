
#include "gem.h"


short
scrp_write (const char *Scrappath)
{
	aes_addrin[0] = (long) Scrappath;
	
	aes_control[0] = 81;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
