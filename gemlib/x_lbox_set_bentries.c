/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** This Function sets the number of items (the subdivisions) for Slider B.
 *
 *  @param box Pointer to the list box structure
 *  @param entries Number of items
 *  @param global_aes global AES array
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

void
mt_lbox_set_bentries( LIST_BOX *box, short entries, short *global_aes )
{
	AES_PARAMS(175,2,0,1,0);

	aes_intin[0]	= 6;
	aes_intin[1]	= entries;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);
}
