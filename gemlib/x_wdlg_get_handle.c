#include "gem_aesP.h"
#include "gemx.h"


short
wdlg_get_handle (DIALOG *dialog)
{
	aes_intin[0]	= 3;
	
	aes_addrin[0]	= (long) dialog;
	
	aes_control[0] = 164;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
