/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** closes the window of the font selector.
 *
 *  @param fnt_dialog Pointer to management structure
 *  @param x will contain the Last x-coordinate of the dialog \n
 *             [option CHECK_NULLPTR] x may be NULL
 *  @param y will contain the Last y-coordinate of the dialog \n
 *             [option CHECK_NULLPTR] y may be NULL
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fnts_xx() functions availability
 *
 *	Note: Old WDIALOG versions do not return the window coordinates. In
 *	that case the binding enters -1, so that the
 *	dialog will be centred automatically at the next call.
 *
 */

short 
mt_fnts_close(FNT_DIALOG *fnt_dialog, short *x, short *y, short *global_aes)
{
	AES_PARAMS(183,0,3,1,0);
                    
	aes_addrin[0] = (long)fnt_dialog;
	aes_intout[1] = -1;	/* ab 6: Position kommt zurÅck */
	aes_intout[2] = -1;

	AES_TRAP(aes_params);
	
#if CHECK_NULLPTR
	if (x)
#endif
	*x = aes_intout[1];
#if CHECK_NULLPTR
	if (y)
#endif
	*y = aes_intout[2];
	
	return aes_intout[0];
}
