#include "gem_aesP.h"
#include "gemx.h"


void *
edit_create (void)
{
	aes_control[0] = 210;
	aes_control[1] = 0;
	aes_control[2] = 0;
	aes_control[3] = 0;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (void *) aes_addrout[0];
}