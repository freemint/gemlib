#include "gem_aesP.h"
#include "gemx.h"


short
edit_cursor (OBJECT *tree, short obj, short whdl, short show)
{
	aes_intin[0] = obj;
	aes_intin[1] = whdl;
	aes_intin[2] = show;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 214;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
