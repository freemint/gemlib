
#include "gemx.h"


int
pdlg_close (PRN_DIALOG * prn_dialog, int *x, int *y)
{
	aes_intout[1] = -1;
	aes_intout[2] = -1;
	aes_addrin[0] = (long) prn_dialog;
	aes_control[0] = 203;
	aes_control[1] = 0;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*x = aes_intout[1];
	*y = aes_intout[2];
	return aes_intout[0];
}
