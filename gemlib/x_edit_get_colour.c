#include "gemx.h"
#include "gem_aesP.h"


short
edit_get_colour (OBJECT *tree, short obj, short *tcolour, short *bcolour)
{
	aes_intin[0] = obj;
	aes_intin[1] = 2;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*tcolour = aes_intout[1];
	*bcolour = aes_intout[2];
	return aes_intout[0];
}
