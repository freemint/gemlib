#include "gem_aesP.h"
#include "gemx.h"


short
wdlg_set_tree (DIALOG *dialog, OBJECT *new_tree)
{
	aes_intin[0]	= 1;
	
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) new_tree;
	
	aes_control[0] = 165;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 2;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
