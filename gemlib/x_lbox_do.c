#include "gemx.h"
#include "gem_aesP.h"


short
lbox_do (LIST_BOX *box, short obj)
{
	aes_intin[0] = obj;
	
	aes_addrin[0] = (long) box;
	
	aes_control[0] = 172;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
