/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** returns the variable \p user_data that was passed at the 
 *  mt_wdlg_create() call.
 *
 *  @param dialog Pointer to the dialog structure
 *  @param global_aes global AES array
 *
 *  @return The pointer user_data
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

void *
mt_wdlg_get_udata( DIALOG *dialog, short *global_aes )
{
	AES_PARAMS(164,1,0,1,0);

	aes_intin[0] = 2;

	aes_addrin[0] = (long) dialog;

	AES_TRAP(aes_params);

	return (void *) aes_addrout[0];
}
