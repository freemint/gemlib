
#include "gemx.h"


short
fnts_update (FNT_DIALOG * fnt_dialog, short button_flags, long id, long pt,
	     long ratio)
{
	unsigned short *i;

	aes_intin[0] = 2;
	aes_intin[1] = button_flags;
	i = (unsigned short *) &id;
	aes_intin[2] = i[0];
	aes_intin[3] = i[1];
	i = (unsigned short *) &pt;
	aes_intin[4] = i[0];
	aes_intin[5] = i[1];
	i = (unsigned short *) &ratio;
	aes_intin[6] = i[0];
	aes_intin[7] = i[1];
	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 185;
	aes_control[1] = 8;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
