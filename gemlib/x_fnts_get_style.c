#include "gem_aesP.h"
#include "gemx.h"


long
fnts_get_style (FNT_DIALOG * fnt_dialog, long id, short index)
{
	unsigned short *i;

	aes_intin[0] = 1;
	i = (unsigned short *) &id;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	aes_intin[3] = index;
	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 184;
	aes_control[1] = 4;
	aes_control[2] = 2;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	i = (unsigned short *) &aes_intout[0];
	return *(long *) i;
}
