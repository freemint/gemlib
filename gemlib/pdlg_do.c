#include "gem_aesP.h"
#include "gemx.h"


short
pdlg_do (PRN_DIALOG * prn_dialog, PRN_SETTINGS * settings,
	 char *document_name, short option_flags)
{
	aes_intin[0] = option_flags;
	aes_addrin[0] = (long) prn_dialog;
	aes_addrin[1] = (long) settings;
	aes_addrin[3] = (long) document_name;
	aes_control[0] = 207;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 3;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
