#include "gemx.h"
#include "gem_aesP.h"


FNT_DIALOG *
fnts_create (short vdi_handle, short no_fonts, short font_flags, short dialog_flags,
	     char *sample, char *opt_button)
{
	aes_intin[0] = vdi_handle;
	aes_intin[1] = no_fonts;
	aes_intin[2] = font_flags;
	aes_intin[3] = dialog_flags;
	aes_addrin[0] = (long) sample;
	aes_addrin[1] = (long) opt_button;
	aes_control[0] = 180;
	aes_control[1] = 4;
	aes_control[2] = 0;
	aes_control[3] = 4;
	aes_control[4] = 1;
	aes (&aes_params);
	return (FNT_DIALOG *) aes_addrout[0];
}
