
#include "gemx.h"


void
fnts_remove (FNT_DIALOG * fnt_dialog)
{
	aes_intin[0] = 1;

	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 185;
	aes_control[1] = 1;
	aes_control[2] = 0;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
}
