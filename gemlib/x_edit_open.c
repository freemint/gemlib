#include "gem_aesP.h"
#include "gemx.h"


short
edit_open (OBJECT *tree, short obj)
{
	aes_intin[0] = obj;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 211;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
