/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the pointer to the object tree of the dialog box
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return Pointer to the object tree of the dialog
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

OBJECT *
mt_lbox_get_tree( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(174,1,0,1,0);

	aes_intin[0]	= 1;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return((OBJECT  *)aes_addrout[0]);
}
