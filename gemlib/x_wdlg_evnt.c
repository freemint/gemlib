
#include "gemx.h"


short
wdlg_evnt (DIALOG *dialog, EVNT *events)
{
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) events;
	
	aes_control[0] = 166;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
