
#include "gem.h"


short
appl_trecord (void *Mem, short Count)
{
	aes_intin[0] = Count;
	
	aes_addrin[0] = (long) Mem;
	
	aes_control[0] = 15;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
