#include "gem_aesP.h"
#include "gemx.h"


short
fnts_delete (FNT_DIALOG * fnt_dialog, short vdi_handle)
{
	aes_intin[0] = vdi_handle;
	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 181;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
