/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "gemx.h"

/** Memory for printer settings is allocated, the structure is initialised 
 *  and returned
 *
 *  @param prn_dialog Pointer to management structure
 *  @param global_aes global AES array
 *
 *  @return Printer settings
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

PRN_SETTINGS *
mt_pdlg_new_settings(PRN_DIALOG *prn_dialog, short *global_aes)
{
	AES_PARAMS(205,1,0,1,1);

	aes_intin[0] = 5;
	
	aes_addrin[0] = (long)prn_dialog;

	AES_TRAP(aes_params);
	
	return (PRN_SETTINGS*) aes_addrout[0];
}
