
#include "gem.h"


short
shel_envrn (char **result, const char *param)
{
	aes_addrin[0] = (long) result;
	aes_addrin[1] = (long) param;
	
	aes_control[0] = 125;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
