/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** evaluates the passed EVNT structure and calls mt_wdlg_evnt() internally.
 *
 *  @param prn_dialog Pointer to management structure
 *  @param settings Printer settings
 *  @param events Pointer to EVNT structure
 *  @param button Selected button (or 0)
 *         - PDLG_CANCEL (1)   "Cancel" was selected 
 *         - PDLG_OK	 (2)   "OK" was pressed 
 *  @param global_aes global AES array
 *
 *  @return 0 (Exit button selected) or 1 (Nothing happened)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  mt_pdlg_evnt() evaluates the passed EVNT structure and calls mt_wdlg_evnt() 
 *  internally. If one of the exit buttons was activated ("Cancel", "OK", 
 *  "Set", "Mark" or "Options") the function returns a 0 and the button that 
 *  the user has selected is returned in \p button. If the dialog was confirmed, 
 *  then the new printer settings are returned in \p settings.
 *
 */

short 
mt_pdlg_evnt(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, EVNT *events,
             short *button, short *global_aes)
{
	AES_PARAMS(206,0,2,3,0);

	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)settings;
	aes_addrin[2] = (long)events;

	AES_TRAP(aes_params);

	*button = aes_intout[1];
	
	return aes_intout[0];
}
