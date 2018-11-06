#include "gem_aesP.h"
#include "mt_gemx.h"

/** activates an edit object, i.e. the cursor will be drawn 
 *  in object \p obj and deleted from any previously active object.
 *
 *  @param dialog Pointer to the dialog structure
 *  @param obj Number of the new edit object
 *         (or 0, if none is to be active)
 *  @param global_aes global AES array
 *
 *  @return Number of the current edit object
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_set_edit( DIALOG *dialog, short obj, short *global_aes )
{
	AES_PARAMS(165,2,1,1,0);

	aes_intin[0]	= 0;
	aes_intin[1]	= obj;

	aes_addrin[0]	= (long)dialog;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
