
#include "gemx.h"


void
edit_set_buf (OBJECT *tree, short obj, char *buf, long buflen)
{
	aes_intin[0] = obj;
	aes_intin[1] = 0;
	*(long *) (aes_intin+2) = buflen;
	
	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) buf;
	
	aes_control[0] = 217;
	aes_control[1] = 4;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
