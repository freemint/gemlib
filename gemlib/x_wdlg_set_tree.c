/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** represents a new object tree in a dialog. If the new root 
 *  object has a different size, the window size will be adapted to suit.
 *  The window contents will be updated in each case.
 *
 *  @param dialog Pointer to the dialog structure
 *  @param new_tree Pointer to the new object tree
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_set_tree( DIALOG *dialog, OBJECT *new_tree, short *global_aes )
{
	AES_PARAMS(165,1,1,2,0);

	aes_intin[0]	= 1;

	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)new_tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
