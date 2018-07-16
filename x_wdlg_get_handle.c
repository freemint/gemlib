/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the handle of the dialog window
 *
 *  @param dialog Pointer to the dialog structure
 *  @param global_aes global AES array
 *
 *  @return Window handle
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_get_handle( DIALOG *dialog, short *global_aes )
{
	AES_PARAMS(164,1,1,1,0);

	aes_intin[0] = 3;

	aes_addrin[0] = (long)dialog;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
