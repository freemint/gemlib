#include "gemx.h"
#include "gem_aesP.h"


void
lbox_bscroll_to (LIST_BOX *box, short first, GRECT *box_rect, GRECT *slider_rect)
{
	aes_intin[0] = 7;
	aes_intin[1] = first;
	
	aes_addrin[0] = (long) box;
	aes_addrin[1] = (long) box_rect;
	aes_addrin[2] = (long) slider_rect;
	
	aes_control[0] = 175;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 3;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
