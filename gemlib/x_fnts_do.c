#include "gemx.h"
#include "gem_aesP.h"


short
fnts_do (FNT_DIALOG * fnt_dialog, short button_flags, long id_in, long pt_in,
	 long ratio_in, short *check_boxes, long *id, long *pt, long *ratio)
{
	unsigned short *i;

	aes_intin[0] = button_flags;
	i = (unsigned short *) &id_in;
	aes_intin[1] = i[0];
	aes_intin[2] = i[1];
	i = (unsigned short *) &pt_in;
	aes_intin[3] = i[0];
	aes_intin[4] = i[1];
	i = (unsigned short *) &ratio_in;
	aes_intin[5] = i[0];
	aes_intin[6] = i[1];
	aes_addrin[0] = (long) fnt_dialog;
	aes_control[0] = 187;
	aes_control[1] = 7;
	aes_control[2] = 8;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*check_boxes = aes_intout[1];
	*id = ((long) aes_intout[2] << 16) | (aes_intout[3]);
	*pt = ((long) aes_intout[4] << 16) | (aes_intout[5]);
	*ratio = ((long) aes_intout[6] << 16) | (aes_intout[7]);
	return aes_intout[0];
}
