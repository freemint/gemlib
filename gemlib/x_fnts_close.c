#include "gem_aesP.h"
#include "gemx.h"


short
fnts_close (FNT_DIALOG * fnt_dialog, short *x, short *y)
{
	aes_addrin[0] = (long) fnt_dialog;
	aes_intout[1] = -1;	/* ab 6: Position kommt zurÅck */
	aes_intout[2] = -1;
	aes_control[0] = 183;
	aes_control[1] = 0;
	aes_control[2] = 3;
	aes_control[3] = 1;
	aes_control[4] = 0;
	aes (&aes_params);
	*x = aes_intout[1];
	*y = aes_intout[2];
	return aes_intout[0];
}
