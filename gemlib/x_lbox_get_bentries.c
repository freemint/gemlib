/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** returns the number of items for Slider B.
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return Number of items
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

short
mt_lbox_get_bentries( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(174,1,1,1,0);

	aes_intin[0]	= 11;
	
	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
