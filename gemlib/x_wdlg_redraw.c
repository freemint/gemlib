#include "gem_aesP.h"
#include "gemx.h"


void
wdlg_redraw (DIALOG *dialog, GRECT *rect, short obj, short depth)
{
	aes_intin[0]	= obj;
	aes_intin[1]	= depth;
	
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) rect;
	
	aes_control[0] = 167;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
}
