#include "gem_aesP.h"
#include "mt_gemx.h"

/** Change the size of memory allocated with x_malloc. 
 *
 *  @param addr
 *  @param size
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_realloc(void **addr, long size, short *global_aes)
{
	AES_PARAMS(0x7189,2,1,1,0);

	aes_intin_long(0) = size;
	aes_addrin[0] = (long)addr;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
