/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** This function positions Slider B and draws it within the redraw rectangle.
 *
 *  @param box Pointer to the list box structure
 *  @param first Index of the first visible entry
 *  @param rect Pointer to redraw rectangle or 0L
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function positions Slider B and draws it within the redraw 
 *  rectangle \p rect. The contents of the list box will not be updated, 
 *  so one may have to call mt_lbox_update().
 *  If \p rect is 0L, then only the position of the slider objects will 
 *  be altered, but the objects will not be drawn.
 *
 */

void
mt_lbox_set_bsldr( LIST_BOX *box, short first, GRECT *rect, short *global_aes )
{
	AES_PARAMS(175,2,0,2,0);

	aes_intin[0]	= 5;
	aes_intin[1]	= first;
	
	aes_addrin[0]	= (long)box;
	aes_addrin[1]	= (long)rect;

	AES_TRAP(aes_params);
}
