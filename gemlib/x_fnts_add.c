
#include "gemx.h"


short
fnts_add (FNT_DIALOG * fnt_dialog, FNTS_ITEM * user_fonts)
{
	aes_intin[0] = 0;
	aes_addrin[0] = (long) fnt_dialog;
	aes_addrin[1] = (long) user_fonts;
	aes_control[0] = 185;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
