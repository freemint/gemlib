#include "gemx.h"
#include "gem_aesP.h"


short
wdlg_open (DIALOG *dialog, char *title, short kind,
short x, short y, short code, void *data)
{
	aes_intin[0]	= kind;
	aes_intin[1]	= x;
	aes_intin[2]	= y;
	aes_intin[3]	= code;
	
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) title;
	aes_addrin[2]	= (long) data;
	
	aes_control[0] = 161;
	aes_control[1] = 4;
	aes_control[2] = 1;
	aes_control[3] = 3;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
