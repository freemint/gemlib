#include "gem_aesP.h"
#include "gemx.h"


short
pdlg_add_sub_dialogs (PRN_DIALOG * prn_dialog, PDLG_SUB * sub_dialogs)
{
	aes_intin[0] = 3;
	aes_addrin[0] = (long) prn_dialog;
	aes_addrin[1] = (long) sub_dialogs;
	aes_control[0] = 205;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
