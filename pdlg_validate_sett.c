/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Validate the printer settings and if necessary correct the structure 
 *  contents.
 *
 *  @param prn_dialog Pointer to management structure
 *  @param settings Printer settings
 *  @param global_aes global AES array
 *
 *  @return 0: Error  \n  1: All OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

short 
mt_pdlg_validate_settings(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global_aes)
{
	AES_PARAMS(205,1,1,2,0);

	aes_intin[0] = 8;

	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)settings;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
