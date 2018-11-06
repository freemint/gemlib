#include "gem_aesP.h"
#include "mt_gemx.h"

/** is the counterpart to mt_pdlg_open()/mt_pdlg_evnt()/mt_pdlg_close(). This 
 *  function opens a modal dialog and only returns to the caller when one of 
 *  the exit buttons has been activated ("Cancel", "OK" ).
 *
 *  @param prn_dialog Pointer to management structure
 *  @param settings Printer settings
 *  @param document_name Document name
 *  @param option_flags 
 *         - PDLG_PREFS          0x0000   Display settings dialog
 *         - PDLG_PRINT          0x0001   Display print dialog 
 *         - PDLG_ALWAYS_COPIES  0x0010   Always offer No. of copies 
 *         - PDLG_ALWAYS_ORIENT  0x0020   Always offer landscape format 
 *         - PDLG_ALWAYS_SCALE   0x0040   Always offer scaling 
 *         - PDLG_EVENODD        0x0100   Offer option for even and odd pages 
 *  @param global_aes global AES array
 *
 *  @return Selected button (or 0)
 *         - PDLG_CANCEL 1     "Cancel" was selected 
 *         - PDLG_OK	 2     "OK" was pressed 
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

short
mt_pdlg_do(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, char *document_name,
           short option_flags, short *global_aes)
{
	AES_PARAMS(207,1,1,3,0);

	aes_intin[0] = option_flags;
	
	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)settings;
	aes_addrin[3] = (long)document_name;
	aes_intout[0] = 0;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
