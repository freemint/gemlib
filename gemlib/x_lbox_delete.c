/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** releases the memory allocated for the list box.
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *  @return 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 */

short
mt_lbox_delete( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(173,0,1,1,0);

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);

	return(aes_intout[0]);
}
