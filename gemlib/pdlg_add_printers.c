#include "gemx.h"
#include "gem_aesP.h"


short
pdlg_add_printers (PRN_DIALOG * prn_dialog, DRV_INFO * drv_info)
{
	aes_intin[0] = 0;
	aes_addrin[0] = (long) prn_dialog;
	aes_addrin[1] = (long) drv_info;
	aes_control[0] = 205;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
