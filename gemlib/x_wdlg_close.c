#include "gemx.h"
#include "gem_aesP.h"


short
wdlg_close (DIALOG *dialog, short *x, short *y)
{
	aes_intout[1] = -1;
	aes_intout[2] = -1;
	
	aes_addrin[0]	= (long) dialog;
	
	aes_control[0] = 162;
	aes_control[1] = 0;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	if (x) *x = aes_intout[1];
	if (y) *y = aes_intout[2];
	
	return aes_intout[0];
}
