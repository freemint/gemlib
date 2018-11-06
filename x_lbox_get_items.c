#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns a pointer to the list of the LBOX_ITEMs
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return Pointer to the chained list
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

LBOX_ITEM  *
mt_lbox_get_items( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(174,1,0,1,1);

	aes_intin[0]	= 6;
	
	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return (LBOX_ITEM *) aes_addrout[0];
}
