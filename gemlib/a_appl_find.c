
#include "gem.h"


short
appl_find (const char *Name)
{
	aes_addrin[0] = (long) Name;
	
	aes_control[0] = 13;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
