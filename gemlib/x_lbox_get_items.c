#include "gemx.h"
#include "gem_aesP.h"


LBOX_ITEM *
lbox_get_items (LIST_BOX *box)
{
	aes_intin[0] = 6;
	
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 174;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (LBOX_ITEM *) aes_addrout[0];
}
