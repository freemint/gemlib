
#include "gemx.h"


int
fnts_get_info (FNT_DIALOG * fnt_dialog, long id, int *mono, int *outline)
{
	unsigned short *i;

	aes_intin[0] = 3;
	i = (unsigned short *) &id;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 184;
	aes_control[1] = 3;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*mono = aes_intout[1];
	*outline = aes_intout[2];
	return aes_intout[0];
}
