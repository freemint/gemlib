/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** updates the contents of the list box objects
 *
 *  @param box Pointer to the list box structure
 *  @param rect Pointer to the redraw GRECT or 0L
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function updates the contents of the list box objects, i.e. the function 
 *  \p set is called for each of the objects. If \p rect is not 0L
 *  it will be regarded as a pointer to a GRECT that will be used for the 
 *  redraw of the list box. Otherwise the objects will only be updated but 
 *  not drawn.
 *
 */

void
mt_lbox_update( LIST_BOX *box, GRECT *rect, short *global_aes )
{
	AES_PARAMS(171,0,0,2,0);

	aes_addrin[0] = (long)box;
	aes_addrin[1] = (long)rect;

	AES_TRAP(aes_params);
}
