#include "gem_aesP.h"
#include "gemx.h"


short
wdlg_set_edit (DIALOG *dialog, short obj)
{
	aes_intin[0]	= 0;
	aes_intin[1]	= obj;
	
	aes_addrin[0]	= (long) dialog;
	
	aes_control[0] = 165;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
