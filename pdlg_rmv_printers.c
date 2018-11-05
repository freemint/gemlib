/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** removes the printers installed with mt_pdlg_add_printers() from the binding.
 *
 *  @param prn_dialog Pointer to management structure
 *  @param global_aes global AES array
 *
 *  @return unknown ???
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  @note mt_pdlg_remove_printers() must be called before mt_pdlg_delete().
 *
 */

short
mt_pdlg_remove_printers(PRN_DIALOG *prn_dialog, short *global_aes)
{
	AES_PARAMS(205,1,1,1,0);

	aes_intin[0] = 1;

	aes_addrin[0] = (long) prn_dialog;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
