/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** returns a pointer to item \p n of the list
 *
 *  @param box Pointer to the list box structure
 *  @param n Index des items
 *  @param global_aes global AES array
 *
 *  @return Pointer to item n or 0L
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

LBOX_ITEM  *
mt_lbox_get_item( LIST_BOX *box, short n, short *global_aes )
{
	AES_PARAMS(174,2,0,1,0);

	aes_intin[0]	= 7;
	aes_intin[1]	= n;
	
	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return (LBOX_ITEM *) aes_addrout[0];
}
