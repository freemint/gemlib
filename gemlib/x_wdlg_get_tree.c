/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** returns the size of the object tree and the size of the 
 *  window (of the working area). If the dialog size has not been altered 
 *  with mt_wdlg_set_size(), then the working area corresponds to the GRECT of 
 *  the root object.
 *
 *  @param dialog Pointer to the dialog structure
 *  @param tree Pointer to object tree
 *  @param r Pointer to GRECT
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_get_tree( DIALOG *dialog, OBJECT **tree, GRECT *r, short *global_aes )
{
	AES_PARAMS(164,1,1,3,0);

	aes_intin[0]	= 0;

	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)tree;
	aes_addrin[2]	= (long)r;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
