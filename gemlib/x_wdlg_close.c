/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** closes the window dialog
 *
 *  @param dialog Pointer to the dialog structure
 *  @param x Last x-coordinate of the dialog
 *  @param y Last y-coordinate of the dialog
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 *  @note: Old WDIALOG versions do not return the window coordinates. In 
 *  that case the binding enters -1, so that the dialog will be centred 
 *  automatically at the next call.
 *
 */

short
mt_wdlg_close( DIALOG *dialog, short *x, short *y, short *global_aes )
{
	AES_PARAMS(162,0,3,1,0);

	aes_intout[1] = -1;
	aes_intout[2] = -1;

	aes_addrin[0] = (long)dialog;

	AES_TRAP(aes_params);

	if (x) *x = aes_intout[1];
	if (y) *y = aes_intout[2];

	return aes_intout[0];
}
