#include "gem_aesP.h"
#include "gemx.h"


short
wdlg_set_size (DIALOG *dialog, GRECT *new_size)
{
	aes_intin[0]	= 2;
	
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) new_size;
	
	aes_control[0] = 165;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
