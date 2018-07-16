/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** reacts to the activation of a button
 *
 *  @param box Pointer to the list box structure
 *  @param obj Number of the selected object
 *  @param global_aes global AES array
 *
 *  @return Number of the selected object
 *		    or -1, if there was a double-click
 *		    on an entry
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  mt_lbox_do() reacts to the activation of a button. This function should be called 
 *  after mt_form_do() (or by the service function of the window dialog). If one 
 *  of the entries of the list box was selected with a double-click, mt_lbox_do() 
 *  returns -1. The dialog should then be closed as if the OK button had 
 *  been activated.
 *  
 *  mt_lbox_do() recognises double-clicks by the set topmost bit of the object 
 *  number \p obj (object number | 0x8000). For the returned object number 
 *  \p slct_obj the top bit is always cleared.
 *  
 */

short
mt_lbox_do( LIST_BOX *box, short obj, short *global_aes )
{
	AES_PARAMS(172,1,1,1,0);

	aes_intin[0]	= obj;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return(aes_intout[0]);
}
