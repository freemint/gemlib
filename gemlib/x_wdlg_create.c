#include "gem_aesP.h"
#include "gemx.h"


DIALOG *
wdlg_create (HNDL_OBJ handle_exit, OBJECT *tree, void *user_data, short code,
void *data, short flags)
{
	aes_intin[0]	= code;
	aes_intin[1]	= flags;
	
	aes_addrin[0]	= (long) handle_exit;
	aes_addrin[1]	= (long) tree;
	aes_addrin[2]	= (long) user_data;
	aes_addrin[3]	= (long) data;
	
	aes_control[0] = 160;
	aes_control[1] = 2;
	aes_control[2] = 0;
	aes_control[3] = 4;
	aes_control[4] = 0;
	
	aes (&aes_params);
	
	return (DIALOG *) aes_addrout[0];
}
