#include "gemx.h"
#include "gem_aesP.h"


short
pdlg_evnt (PRN_DIALOG * prn_dialog, PRN_SETTINGS * settings, EVNT * events,
	   short *button)
{
	aes_addrin[0] = (long) prn_dialog;
	aes_addrin[1] = (long) settings;
	aes_addrin[2] = (long) events;
	aes_control[0] = 206;
	aes_control[1] = 0;
	aes_control[2] = 2;
	aes_control[3] = 3;
	aes_control[4] = 0;
	aes (&aes_params);
	*button = aes_intout[1];
	return aes_intout[0];
}
