#include "gemx.h"
#include "gem_aesP.h"


void
lbox_set_asldr (LIST_BOX *box, short first, GRECT *rect)
{
	aes_intin[0] = 0;
	aes_intin[1] = first;
	
	aes_addrin[0] = (long) box;
	aes_addrin[1] = (long) rect;
	
	aes_control[0] = 175;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
