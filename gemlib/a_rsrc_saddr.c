
#include "gem.h"


short
rsrc_saddr (short Type, short Index, void *Address)
{
	aes_intin[0] = Type;
	aes_intin[1] = Index;
	
	aes_addrin[0] = (long) Address;
	
	aes_control[0] = 113;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
