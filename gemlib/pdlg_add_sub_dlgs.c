/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "gemx.h"

/** Add application's sub-dialogs
 *
 *  @param prn_dialog Pointer to management structure
 *  @param sub_dialogs List of sub-dialogs
 *  @param global_aes global AES array
 *
 *  @return 0: Error  \n 1: All OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  With mt_pdlg_add_sub_dialogs() an application can add its custom 
 *  sub-dialogs to the printer dialog to offer special print options (e.g. 
 *  watermarks, background images etc.).
 *
 *  @note The hooking in of an application's own dialogs is demonstrated in the 
 *  sample programs PDLGSMP3.C and PDLGSMP4.C (of WDIALOG documentation).
 *  
 */

short
mt_pdlg_add_sub_dialogs(PRN_DIALOG *prn_dialog, PDLG_SUB *sub_dialogs, short *global_aes)
{
	AES_PARAMS(205,1,1,2,0);

	aes_intin[0] = 3;

	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)sub_dialogs;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
