#include "gemx.h"
#include "gem_aesP.h"


void
edit_get_scrollinfo (OBJECT *tree, short obj, long *nlines, long *yscroll,
short *yvis, short *yval, short *ncols, short *xscroll,
short *xvis)
{
	aes_intin[0] = obj;
	aes_intin[1] = 9;
	
	aes_addrin[0] = (long) tree;
	
	aes_control[0] = 216;
	aes_control[1] = 2;
	aes_control[2] = 6;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	*nlines = *((long *) (aes_intout+1));
	*yscroll = *((long *) (aes_intout+3));
	*yvis = aes_intout[5];
	*yval = aes_intout[6];
	*ncols = aes_intout[7];
	*xscroll = aes_intout[8];
	*xvis = aes_intout[9];
}
