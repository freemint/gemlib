#include "gem_aesP.h"
#include "mt_gemx.h"

/** This function positions Slider B and updates the contents of the list box
 *
 *  @param box Pointer to the list box structure
 *  @param first Index of the first visible entry
 *  @param box_rect Pointer to redraw rectangle or 0L
 *  @param slider_rect Pointer to redraw rectangle or 0L
 *  @param global_aes global AES array
 *
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function positions Slider B and updates the contents of the list 
 *  box. \p box_rect is the redraw rectangle for the list box and 
 *  \p slider_rect is the redraw rectangle for the slider.
 *  
 *  mt_lbox_bscroll_to() works in principle like a call of mt_lbox_set_bslider() followed 
 *  by a mt_lbox_update(); scrolling takes place if possible, however, to 
 *  reduce the amount of drawing required.
 *  One may therefore not use mt_lbox_scroll_to() if the item list of the list 
 *  box has changed.
 *  
 */

void
mt_lbox_bscroll_to( LIST_BOX *box, short first, GRECT *box_rect,
					GRECT *slider_rect, short *global_aes )
{
	AES_PARAMS(175,2,0,3,0);

	aes_intin[0]	= 7;
	aes_intin[1]	= first;
	
	aes_addrin[0]	= (long)box;
	aes_addrin[1]	= (long)box_rect;
	aes_addrin[2]	= (long)slider_rect;

	AES_TRAP(aes_params);
}
