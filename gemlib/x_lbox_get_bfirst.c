/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the index of the first visible item (Slider B!).
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return Index of the first visible item
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

short
mt_lbox_get_bfirst( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(174,1,1,1,0);

	aes_intin[0]	= 12;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
