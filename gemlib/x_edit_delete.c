#include "gem_aesP.h"
#include "gemx.h"


void
edit_delete (void *xi)
{
	aes_addrin[0] = (long) xi;
	
	aes_control[0] = 213;
	aes_control[1] = 0;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
