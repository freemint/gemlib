
#include "gem.h"


short
objc_sysvar (short mode, short which, short in1, short in2, short *out1, short *out2)
{
	aes_intin[0] = mode;
	aes_intin[1] = which;
	aes_intin[2] = in1;
	aes_intin[3] = in2;
	
	aes_control[0] = 48;
	aes_control[1] = 4;
	aes_control[2] = 3;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*out1 = aes_intout[1];
	*out2 = aes_intout[2];
	
	return aes_intout[0];
}
