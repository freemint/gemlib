
#include "gemx.h"


short
pdlg_free_settings (PRN_SETTINGS * settings)
{
	aes_intin[0] = 6;
	aes_addrin[0] = (long) settings;
	aes_control[0] = 205;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
