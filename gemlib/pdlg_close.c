/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "gemx.h"

/** closes the window of the print dialog
 *
 *  @param prn_dialog Pointer to management structure
 *  @param x X-coordinates of the window
 *  @param y Y-coordinates of the window
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

short
mt_pdlg_close(PRN_DIALOG *prn_dialog, short *x, short *y, short *global_aes)
{
	AES_PARAMS(203,0,3,1,0);

	aes_intout[1] = -1;
	aes_intout[2] = -1;

	aes_addrin[0] = (long)prn_dialog;

	AES_TRAP(aes_params);

	*x = aes_intout[1];
	*y = aes_intout[2];
	
	return aes_intout[0];
}
