/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** opens a window with the print dialog
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
 *  @param x X-coordinates of the window or -1 (centred)
 *  @param y Y-coordinates of the window or -1 (centred)
 *  @param global_aes global AES array
 *
 *  @return Handle of the window or 0 (error)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 *  mt_pdlg_open() opens a window with the print dialog. The handle of the 
 *  window will be returned if no error has arisen. In case of error the 
 *  return value is 0. The structure \p settings contains the printer 
 *  settings, which should be saved with each document. If no settings exist 
 *  for a document yet, one can either create them with mt_pdlg_new_settings() 
 *  (the memory block belongs to the system) or the application can call 
 *  Malloc() and subsequently mt_pdlg_dflt_settings() to initialise the memory.
 *  
 *  \p option_flags contains information, among other things, whether the 
 *  dialog is to be displayed as a settings (PDLG_PREFS) or print dialog 
 *  (PDLG_PRINT). In addition the flags PDLG_ALWAYS_COPIES, PDLG_ALWAYS_ORIENT 
 *  and PDLG_ALWAYS_SCALE can ensure that the number of copies, landscape 
 *  printing and scaling options are offered even when the driver does not 
 *  support them, so that the application has to output the page rotated to 
 *  the landscape format, for instance. PDLG_EVENODD makes the buttons for 
 *  even/odd pages selectable.
 *
 */

short
mt_pdlg_open(PRN_DIALOG *prn_dialog, PRN_SETTINGS *settings, char *document_name,
             short option_flags, short x, short y, short *global_aes)
{
	AES_PARAMS(202,3,1,3,0);

	aes_intin[0] = option_flags;
	aes_intin[1] = x;
	aes_intin[2] = y;
	
	aes_addrin[0] = (long)prn_dialog;
	aes_addrin[1] = (long)settings;
	aes_addrin[2] = (long)document_name;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
