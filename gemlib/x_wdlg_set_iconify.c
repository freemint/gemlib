#include "gemx.h"
#include "gem_aesP.h"


short
wdlg_set_iconify (DIALOG *dialog, GRECT *g, char *title, OBJECT *tree, short obj)
{
	aes_intin[0]	= 3;
	aes_intin[1]	= obj;
	
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) g;
	aes_addrin[2]	= (long) title;
	aes_addrin[3]	= (long) tree;
	
	aes_control[0] = 165;
	aes_control[1] = 2;
	aes_control[2] = 1;
	aes_control[3] = 4;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
