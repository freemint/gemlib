#include "gemx.h"
#include "gem_aesP.h"


short
pdlg_open (PRN_DIALOG * prn_dialog, PRN_SETTINGS * settings,
	   char *document_name, short option_flags, short x, short y)
{
	aes_intin[0] = option_flags;
	aes_intin[1] = x;
	aes_intin[2] = y;
	aes_addrin[0] = (long) prn_dialog;
	aes_addrin[1] = (long) settings;
	aes_addrin[2] = (long) document_name;
	aes_control[0] = 202;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 3;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
