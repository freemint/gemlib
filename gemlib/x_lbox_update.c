
#include "gemx.h"


void
lbox_update (LIST_BOX *box, GRECT *rect)
{
	aes_addrin[0] = (long) box;
	aes_addrin[1] = (long) rect;
	
	aes_control[0] = 171;
	aes_control[1] = 0;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
