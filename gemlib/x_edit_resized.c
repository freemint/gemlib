
#include "gemx.h"


short
edit_resized (OBJECT *tree, short obj, short *oldrh, short *newrh)
{
	aes_intin[0] = obj;
	aes_intin[1] = 6;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 217;
	aes_control[1] = 2;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*oldrh = aes_intout[1];
	*newrh = aes_intout[2];
	return aes_intout[0];
}
