
#include "gemx.h"


short
wdlg_get_tree (DIALOG *dialog, OBJECT **tree, GRECT *r)
{
	aes_intin[0]	= 0;
	
	aes_addrin[0]	= (long) dialog;
	aes_addrin[1]	= (long) tree;
	aes_addrin[2]	= (long) r;
	
	aes_control[0] = 164;
	aes_control[1] = 1;
	aes_control[2] = 1;
	aes_control[3] = 3;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return aes_intout[0];
}
