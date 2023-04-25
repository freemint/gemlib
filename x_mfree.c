#include "gem_aesP.h"
#include "mt_gemx.h"

/** Free memory allocated with x_malloc.
 *
 *  @param addr
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_mfree(void *addr, short *global_aes)
{
	AES_PARAMS(0x7187,0,1,1,0);

	aes_addrin[0] = (long)addr;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
