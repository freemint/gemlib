#include "gem_aesP.h"
#include "gemx.h"


short
edit_scroll (OBJECT *tree, short obj, short whdl, long yscroll, short xscroll)
{
	aes_intin[0] = obj;
	aes_intin[1] = 9;
	aes_intin[2] = whdl;
	*(long *) (aes_intin+3) = yscroll;
	aes_intin[5] = xscroll;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 217;
	aes_control[1] = 6;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
