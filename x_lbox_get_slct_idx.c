#include "gem_aesP.h"
#include "mt_gemx.h"

/** Establish the index of the first selected item
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return Index of the selected item. If no item in the 
 *          list is selected then -1 will be returned.
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

short
mt_lbox_get_slct_idx( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(174,1,1,1,0);

	aes_intin[0]	= 5;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
