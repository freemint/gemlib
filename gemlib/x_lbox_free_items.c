#include "gem_aesP.h"
#include "gemx.h"


void
lbox_free_items (LIST_BOX *box)
{
	aes_intin[0] = 2;
	
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 175;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
