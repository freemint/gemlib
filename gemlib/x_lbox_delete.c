
#include "gemx.h"


short
lbox_delete (LIST_BOX *box)
{
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 173;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
