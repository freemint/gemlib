#include "gemx.h"
#include "gem_aesP.h"


void *
lbox_get_udata (LIST_BOX *box)
{
	aes_intin[0] = 3;
	
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 174;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (void *) aes_addrout[0];
}
