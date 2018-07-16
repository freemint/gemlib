/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** opens a window with the title line \p title at the position \p x, \p y.
 *	Before mt_wdlg_open() returns to the caller, the service routine \p handle_exit
 *	(see above) is called with the function number HNDL_OPEN: \n
 *	handle_exit(dialog, HNDL_OPEN, code, data );
 *
 *  @param dialog Pointer to the dialog structure
 *  @param title Pointer to the window name or 0L
 *  @param kind Window components (NAME/MOVER/CLOSER)
 *  @param x x-coordinate of the dialog or -1 (centred)
 *  @param y y-coordinate of the dialog or -1 (centred)
 *  @param code Is passed to handle_exit() in \p clicks
 *  @param data  Is passed to handle_exit() in \p data
 *  @param global_aes global AES array
 *
 *  @return Handle of the dialog window (0: Error)
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_open( DIALOG *dialog, char *title, short kind,
			  short x, short y, short code, void *data, short *global_aes )
{
	AES_PARAMS(161,4,1,3,0);

	aes_intin[0]	= kind;
	aes_intin[1]	= x;
	aes_intin[2]	= y;
	aes_intin[3]	= code;

	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)title;
	aes_addrin[2]	= (long)data;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
