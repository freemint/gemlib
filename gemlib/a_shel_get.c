
#include "gem.h"


short
shel_get (char *Buf, short Len)
{
	aes_intin[0] = Len;
	
	aes_addrin[0] = (long) Buf;
	
	aes_control[0] = 122;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
