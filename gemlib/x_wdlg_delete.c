/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** releases the memory allocated for a window dialog
 *
 *  @param dialog Pointer to the dialog structure
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_delete( DIALOG *dialog, short *global_aes )
{
	AES_PARAMS(163,0,1,1,0);

	aes_addrin[0] = (long)dialog;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
