#include "gem_aesP.h"
#include "gemx.h"


short
pdlg_update (PRN_DIALOG * prn_dialog, char *document_name)
{
	aes_intin[0] = 2;
	aes_addrin[0] = (long) prn_dialog;
	aes_addrin[1] = 0L;
	aes_addrin[2] = (long) document_name;
	aes_control[0] = 205;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 3;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
