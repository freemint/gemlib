
#include "gemx.h"


void
edit_close (OBJECT *tree, short obj)
{
	aes_intin[0] = obj;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 212;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
