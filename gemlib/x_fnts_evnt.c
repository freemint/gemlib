
#include "gemx.h"


short
fnts_evnt (FNT_DIALOG * fnt_dialog, EVNT * events, short *button,
	   short *check_boxes, long *id, long *pt, long *ratio)
{
	aes_addrin[0] = (long) fnt_dialog;
	aes_addrin[1] = (long) events;
	aes_control[0] = 186;
	aes_control[1] = 0;
	aes_control[2] = 9;
	aes_control[3] = 2;
	aes_control[4] = 0;
	aes (&aes_params);
	*button = aes_intout[1];
	*check_boxes = aes_intout[2];
	*id = ((long) aes_intout[3] << 16) | (aes_intout[4]);
	*pt = ((long) aes_intout[5] << 16) | (aes_intout[6]);
	*ratio = ((long) aes_intout[7] << 16) | (aes_intout[8]);
	return aes_intout[0];
}
