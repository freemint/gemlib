#include "gem_aesP.h"
#include "mt_gemx.h"

/** frees the memory for the chained list from LBOX_ITEMs
 *
 *  @param box Pointer to the list box structure
 *  @param global_aes global AES array
 *
 *
 *  @since mt_appl_getinfo(7) give informations on mt_lbox_xx() functions availability
 *
 *  This function frees the memory for the chained list from LBOX_ITEMs. 
 *  A prerequisite for this is that memory was allocated with Malloc() for 
 *  each item of the list.
 *  
 *  If custom memory management was used for LBOX_ITEMs (e.g. the C 
 *  standard functions), then a custom function must also be called to free 
 *  the memory.
 *  
 */

void
mt_lbox_free_items( LIST_BOX *box, short *global_aes )
{
	AES_PARAMS(175,1,0,1,0);

	aes_intin[0]	= 2;

	aes_addrin[0]	= (long)box;

	AES_TRAP(aes_params);
}
