
#include "gemx.h"


short
edit_get_dirty (OBJECT *tree, short obj)
{
	aes_intin[0] = obj;
	aes_intin[1] = 7;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
