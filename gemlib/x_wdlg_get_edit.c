/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the number of the current edit object. If the 
 *  result is 0, then no edit object is active at the present time.
 *
 *  @param dialog Pointer to the dialog structure
 *  @param cursor Index of the character \n
 *         [option CHECK_NULLPTR] cursor may be NULL
 *  @param global_aes global AES array
 *
 *  @return Number of the current edit object (or 0, if none is active)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 *  @note With old WDIALOG versions \p cursor is not returned. The binding 
 *  ensures that -1 is entered in this case.
 *
 */

short
mt_wdlg_get_edit( DIALOG *dialog, short *cursor, short *global_aes )
{
	AES_PARAMS(164,1,2,1,0);

	aes_intin[0] = 1;
	
	aes_addrin[0] = (long)dialog;

	aes_intout[1] = -1;  /* for old WDIALOG */
	
	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (cursor)
#endif
	*cursor	= aes_intout[1];
	
	return aes_intout[0];
}
