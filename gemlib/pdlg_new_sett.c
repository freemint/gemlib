
#include "gemx.h"


PRN_SETTINGS *
pdlg_new_settings (PRN_DIALOG * prn_dialog)
{
	aes_intin[0] = 5;
	aes_addrin[0] = (long) prn_dialog;
	aes_control[0] = 205;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 1;
	aes (&aes_params);
	return (PRN_SETTINGS *) aes_addrout[0];
}
