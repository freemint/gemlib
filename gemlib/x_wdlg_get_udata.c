
#include "gemx.h"


void *
wdlg_get_udata (DIALOG *dialog)
{
	aes_intin[0]	= 2;
	
	aes_addrin[0] = (long) dialog;
	
	aes_control[0] = 164;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (void *) aes_addrout[0];
}
