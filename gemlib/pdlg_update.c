/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** This function sets a new window name. It should be called when the 
 *  window dialog lies in the background and the user tops a new document 
 *  window.
 *
 *  @param prn_dialog Pointer to management structure
 *  @param document_name New document name
 *  @param global_aes global AES array
 *
 *  @return 0: Error \n 1: All OK
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

short
mt_pdlg_update(PRN_DIALOG *prn_dialog, char *document_name, short *global_aes)
{
	AES_PARAMS(205,1,1,3,0);

	aes_intin[0] = 2;

	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = 0L;
	aes_addrin[2] = (long)document_name;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
