
#include "gemx.h"


void
edit_get_pos (OBJECT *tree, short obj, short *xscroll, long *yscroll,
char **cyscroll, char **cursorpos, short *cx, short *cy)
{
	aes_intin[0] = obj;
	aes_intin[1] = 5;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 6;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*xscroll = aes_intout[1];
	*yscroll = *((long *) (aes_intout+2));
	*cyscroll = (char *) aes_addrout[0];
	*cx = aes_intout[4];
	*cy = aes_intout[5];
	*cursorpos = (char *) aes_addrout[1];
}
