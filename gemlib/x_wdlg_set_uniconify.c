/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** The counterpart to mt_wdlg_set_iconify(). 
 *  The GRECT \p g sets the new position and size of the window (external 
 *  dimensions). Generally one will pass msg+4 here when one has received the 
 *  message WM_UNICONIFIY. UNICONIFY alters the position and size of the root 
 *  object. As one usually displayed a different object tree for iconified 
 *  windows, the original tree can be passed in \p tree (otherwise set 
 *  it to NULL). Furthermore one can specify the original window title if it 
 *  was altered with mt_wdlg_set_iconify().
 *
 *  @param dialog Pointer to the dialog structure
 *  @param g Pointer to GRECT
 *  @param title New window title or NULL
 *  @param tree New window tree or NULL
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability
 *         This function is only present from  WDIALOG 1.05 onwards. If it 
 *         is not present, intout[0] contains a 0.
 *
 */

short
mt_wdlg_set_uniconify( DIALOG *dialog, GRECT *g, char *title,
					   OBJECT *tree, short *global_aes )
{
	AES_PARAMS(165,1,1,4,0);

	aes_intin[0]	= 4;
	
	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)g;
	aes_addrin[2]	= (long)title;
	aes_addrin[3]	= (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
