
#include "gem.h"


short
rsrc_gaddr (short Type, short Index, void *Address)
{
	aes_intin[0] = Type;
	aes_intin[1] = Index;
	
	aes_control[0] = 112;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 0;
	aes_control[4] = 1;
	
	aes (&aes_params);
	
	*((void **) Address) = (void *) aes_addrout[0];
	
	return aes_intout[0];
}
