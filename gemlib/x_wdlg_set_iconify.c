/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** With mt_wdlg_set_iconify() one can iconify a window dialog. The GRECT \p g
 *  sets the new position and size of the window (external dimensions). 
 *  Generally one will pass msg+4 here when one has received the message 
 *  WM_ICONIFIY. But equally one can also pass a GRECT {-1,-1,-1,-1} which 
 *  MagiC uses to ascertain the position.
 *
 *  @param dialog Pointer to the dialog structure
 *  @param g Pointer to GRECT
 *  @param title New window title or NULL
 *  @param tree New window tree or NULL
 *  @param obj Object to be centred or -1
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_wdlg_xx() functions availability.
 *         This function is only present from  WDIALOG 1.05 onwards. If it
 *         is not present, intout[0] contains a 0.
 *
 *  ICONIFY alters the position and size of the root object. As one usually 
 *  wants to display a different object tree for iconified windows, this 
 *  can be passed in \p tree (otherwise set it to NULL).
 *  
 *  Usually such an object tree consists only of the root object (G_BOX) 
 *  and an icon (G_(C)ICON). If the icon (or another object) is to be 
 *  centred in the window, the object number is passed in \p obj, otherwise 
 *  -1. Furthermore one can specify a new window title. However the calling 
 *  routine must ensure that the original title is restored at the 
 *  mt_wdlg_set_uniconify() call.
 *  
 */

short
mt_wdlg_set_iconify( DIALOG *dialog, GRECT *g, char *title,
					 OBJECT *tree, short obj, short *global_aes )
{
	AES_PARAMS(165,2,1,4,0);

	aes_intin[0]	= 3;
	aes_intin[1]	= obj;

	aes_addrin[0]	= (long)dialog;
	aes_addrin[1]	= (long)g;
	aes_addrin[2]	= (long)title;
	aes_addrin[3]	= (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
