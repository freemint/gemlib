
#include "gemx.h"


short
edit_evnt (OBJECT *tree, short obj, short whdl, EVNT *ev, long *errc)
{
	aes_intin[0] = obj;
	aes_intin[1] = whdl;
	
	aes_addrin[0] = (long) tree;
	aes_addrin[1] = (long) ev;
	
	*((long *) (aes_intout+1)) = 0L;
	
	aes_control[0] = 215;
	aes_control[1] = 2;
	aes_control[2] = 3;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*errc = *((long *) (aes_intout+1));
	return aes_intout[0];
}
