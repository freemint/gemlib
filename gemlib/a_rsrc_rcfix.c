
#include "gem.h"


short
rsrc_rcfix (void *rc_header)
{
	aes_addrin[0] = (long) rc_header;
	
	aes_control[0] = 115;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
