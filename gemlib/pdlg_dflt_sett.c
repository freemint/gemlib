/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Initialises the structure to which \p settings points.
 *
 *  @param prn_dialog Pointer to management structure
 *  @param settings Printer settings
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  @note Structure length can be found with mt_pdlg_get_setsize().
 *
 */

short
mt_pdlg_dflt_settings(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global_aes)
{
	AES_PARAMS(205,1,1,2,0);

	aes_intin[0] = 7;
	
	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)settings;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
