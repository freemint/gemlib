/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** This function must be called in an event-loop
 *
 *  @param dialog Pointer to the dialog structure
 *  @param events Pointer to the EVNT-structure
 *  @param global_aes global AES array
 *
 *  @return continue: 0 (Close dialog) or 1 (All OK)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 *  The event-bits that 
 *  refer to the window dialog are cleared in the bit vector \p mwhich.
 *  Following mt_wdlg_evnt() the EVNT-structure of the application can be used 
 *  to evaluate the events intended for it. If mt_wdlg_evnt() returns a 0, the 
 *  window dialog has to be closed (call mt_wdlg_close()).
 *  
 *  Note: The Iconify-event is not supported by  mt_wdlg_evnt(). Those wanting 
 *  to install the Iconifier icon as a window object during mt_wdlg_open() 
 *  therefore have to evaluate this even and handle it themselves. The same 
 *  applies if one want to install the Sizer icon as an object.
 *  
 */

short
mt_wdlg_evnt( DIALOG *dialog, EVNT *events, short *global_aes )
{
	AES_PARAMS(166,0,1,2,0);

	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)events;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
