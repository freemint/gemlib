/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** With mt_wdlg_set_size() one can alter the size of a window dialog. The 
 *  GRECT \p new_size sets the new position and size of the window's working 
 *  area.  mt_wdlg_set_size() does not alter either the position or the size of the 
 *  root object. If the root object is to be moved or enlarged then the 
 *  object dimensions have to be altered before calling mt_wdlg_set_size().
 *
 *  @param dialog Pointer to the dialog structure
 *  @param new_size Pointer to GRECT
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *
 */

short
mt_wdlg_set_size( DIALOG *dialog, GRECT *new_size, short *global_aes )
{
	AES_PARAMS(165,1,1,2,0);

	aes_intin[0]	= 2;
	
	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)new_size;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
