/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "gemx.h"

/** removes the application's custom sub-dialogs
 *
 *  @param prn_dialog Pointer to management structure
 *  @param global_aes global AES array
 *
 *  @return unknown ???
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

short
mt_pdlg_remove_sub_dialogs(PRN_DIALOG *prn_dialog, short *global_aes)
{
	AES_PARAMS(205,1,1,1,0);

	aes_intin[0] = 4;

	aes_addrin[0] = (long)prn_dialog;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
