/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** This function sets a new list with list box entries
 *
 *  @param box Pointer to the list box structure
 *  @param items 
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function sets a new list with list box entries. The old list must 
 *  first be freed with mt_lbox_free_items().
 *
 *  The pointer \p items can also be 0L if the list box is empty 
 *  and contains no entries.
 */

void
mt_lbox_set_items( LIST_BOX *box, LBOX_ITEM *items, short *global_aes )
{
	AES_PARAMS(175,1,0,2,0);

	aes_intin[0]	= 1;
	
	aes_addrin[0]	= (long)box;
	aes_addrin[1]	= (long)items;

	AES_TRAP(aes_params);
}
