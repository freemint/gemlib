#include "gem_aesP.h"
#include "gemx.h"


short
lbox_get_bfirst (LIST_BOX *box)
{
	aes_intin[0] = 12;
	
	aes_addrin[0] = (long)box;
	
	aes_control[0] = 174;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
