
#include "gemx.h"


short
fnts_get_no_styles (FNT_DIALOG * fnt_dialog, long id)
{
	unsigned short *i;

	aes_intin[0] = 0;
	i = (unsigned short *) &id;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 184;
	aes_control[1] = 3;
	aes_control[2] = 1;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	return aes_intout[0];
}
