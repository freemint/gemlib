/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** This function should be called if a program wants to print immediately 
 *  and it is not possible to call mt_pdlg_do() or mt_pdlg_open() and mt_pdlg_evnt() 
 *  (e.g. Calamus-print dialogs).
 *
 *  @param prn_dialog Pointer to management structure
 *  @param settings Printer settings
 *  @param global_aes global AES array
 *
 *  @return 0: Error \n   1: All OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  @note The passed printer settings will be validated (and saved for old drivers).
 *
 */

short
mt_pdlg_use_settings(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, short *global_aes)
{
	AES_PARAMS(205,1,1,2,0);

	aes_intin[0] = 9;

	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)settings;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
