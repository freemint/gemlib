/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** works in a similar way to mt_objc_draw(), but unlike there the 
 *  rectangle list of the dialog window is taken into account
 *
 *  @param dialog Pointer to the dialog structure
 *  @param rect Pointer to the bounding GRECT
 *  @param obj Number of the start object
 *  @param depth Number of the plane/depth
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 *  If one wants 
 *  to draw an object within the dialog then one should always use 
 *  mt_wdlg_redraw() and not mt_objc_draw(). Before calling mt_wdlg_redraw(), just as 
 *  before and after mt_objc_draw(), a mt_wind_update() call is necessary.
 *
 */

void
mt_wdlg_redraw( DIALOG *dialog, GRECT *rect, short obj,
				short depth, short *global_aes )
{
	AES_PARAMS(167,2,0,2,0);

	aes_intin[0]	= obj;
	aes_intin[1]	= depth;

	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)rect;

	AES_TRAP(aes_params);
}
