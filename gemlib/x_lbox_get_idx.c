/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** list box - get item index
 *
 *  @param items Pointer to the first item of the list
 *  @param search Pointer to the item to be found
 *  @param global_aes global AES array
 *
 *  @return Index of the item or -1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function returns the index \p n of the item \p item.
 *  If \p item is not an element of the list, the return value is -1.
 *
 */

short
mt_lbox_get_idx( LBOX_ITEM *items, LBOX_ITEM *search, short *global_aes )
{
	AES_PARAMS(174,1,1,2,0);

	aes_intin[0]	= 9;

	aes_addrin[0]	= (long)items;
	aes_addrin[1]	= (long)search;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
