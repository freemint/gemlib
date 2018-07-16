/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the pointer \p user_data.
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return \p user_data
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

void *
mt_lbox_get_udata( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(174,1,0,1,1);

	aes_intin[0]	= 3;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return (void*) aes_addrout[0];
}
