/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** This functions works exactly the same as mt_lbox_free_items().
 *
 *  @param items Pointer to linked list with LBOX_ITEMs
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This functions works exactly the same as mt_lbox_free_items(). 
 *  In contrast to that however mt_lbox_free_list() is called with the pointer 
 *  on the first LBOX_ITEM of the list.
 *  
 */

void
mt_lbox_free_list( LBOX_ITEM *items, short *global_aes )
{
	AES_PARAMS(175,1,0,1,0);

	aes_intin[0]	= 3;

	aes_addrin[0]	= (long)items;

	AES_TRAP(aes_params);
}
