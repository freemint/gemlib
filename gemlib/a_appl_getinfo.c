
#include "gem.h"


short
appl_getinfo (short type, short *out1, short *out2, short *out3, short *out4)
{
	aes_intin[0] = type;
	
	aes_control[0] = 130;
	aes_control[1] = 1;
	aes_control[2] = 5;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	*out3 = aes_intout[3];
	*out4 = aes_intout[4];
	
	return aes_intout[0];
}
