
#include "gemx.h"


void
edit_set_pos (OBJECT *tree, short obj, short xscroll, long yscroll,
char *cyscroll, char *cursorpos, short cx, short cy)
{
	aes_intin[0] = obj;
	aes_intin[1] = 5;
	aes_intin[2] = xscroll;
	*(long *) (aes_intin+3) = yscroll;
	aes_intin[5] = cx;
	aes_intin[6] = cy;
	
	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) cyscroll;
	aes_addrin[2] = (long) cursorpos;
	
	aes_control[0] = 217;
	aes_control[1] = 7;
	aes_control[2] = 0;
	aes_control[3] = 3;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
