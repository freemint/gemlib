#include "gemx.h"
#include "gem_aesP.h"


PRN_DIALOG *
pdlg_create (short dialog_flags)
{
	aes_intin[0] = dialog_flags;
	aes_control[0] = 200;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 0;
	aes_control[4] = 1;
	aes (&aes_params);
	return (void *) aes_addrout[0];
}
