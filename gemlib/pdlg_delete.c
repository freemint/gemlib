
#include "gemx.h"


short
pdlg_delete (PRN_DIALOG * prn_dialog)
{
	aes_addrin[0] = (long) prn_dialog;
	aes_control[0] = 201;
	aes_control[1] = 0;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
