
#include "gem.h"


short
appl_tplay (void *Mem, short Num, short Scale)
{
	aes_intin[0] = Num;
	aes_intin[1] = Scale;
	
	aes_addrin[0] = (long) Mem;
	
	aes_control[0] = 14;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
