
#include "gemx.h"


void
edit_set_format (OBJECT *tree, short obj, short tabwidth, short autowrap)
{
	aes_intin[0] = obj;
	aes_intin[1] = 1;
	aes_intin[2] = tabwidth;
	aes_intin[3] = autowrap;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 217;
	aes_control[1] = 4;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
