#include "gemx.h"
#include "gem_aesP.h"


short
lbox_get_idx (LBOX_ITEM *items, LBOX_ITEM *search)
{
	aes_intin[0] = 9;
	
	aes_addrin[0] = (long)items;
	aes_addrin[1] = (long)search;
	
	aes_control[0] = 174;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
