/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** allocates memory for a dialog structure and initialises it.
 *
 *  @param handle_exit Pointer to the service function
 *  @param tree Pointer to the object tree
 *  @param user_data Pointer to user info
 *  @param code Is passed to \p handle_exit() as \p clicks parameter
 *  @param data Is passed to \p handle_exit() as \p data parameter
 *  @param flags 
 *  @param global_aes global AES array
 *
 *  @return Pointer to the dialog structure
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 *  @note WDIALOG versions below 1.06 have an error in the edit object 
 *		  handling, which can lead to a crash with object trees with only one
 *		  object (ROOT). If you absolutely want to display an empty window
 *		  dialog, make sure that the tree is made up of at least two objects.
 *
 */

DIALOG *
mt_wdlg_create( HNDL_OBJ handle_exit, OBJECT *tree, void *user_data,
                short code, void *data, short flags, short *global_aes )
{
	AES_PARAMS(160,2,0,4,1);
	
	aes_intin[0]	= code;
	aes_intin[1]	= flags;

	aes_addrin[0]	= (long)handle_exit;
	aes_addrin[1]	= (long)tree;
	aes_addrin[2]	= (long)user_data;
	aes_addrin[3]	= (long)data;

	AES_TRAP(aes_params);

	return (DIALOG *) aes_addrout[0];
}
