#include "gem_aesP.h"
#include "gemx.h"


void
lbox_set_items (LIST_BOX *box, LBOX_ITEM *items)
{
	aes_intin[0] = 1;
	
	aes_addrin[0] = (long) box;
	aes_addrin[1] = (long) items;
	
	aes_control[0] = 175;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
