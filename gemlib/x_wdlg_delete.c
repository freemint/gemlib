
#include "gemx.h"


short
wdlg_delete (DIALOG *dialog)
{
	aes_addrin[0]	= (long) dialog;
	
	aes_control[0] = 163;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
