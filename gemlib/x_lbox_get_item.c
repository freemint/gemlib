
#include "gemx.h"


LBOX_ITEM *
lbox_get_item (LIST_BOX *box, short n)
{
	aes_intin[0] = 7;
	aes_intin[1] = n;
	
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 174;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (LBOX_ITEM *) aes_addrout[0];
}
