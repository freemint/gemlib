#include "gem_aesP.h"
#include "mt_gemx.h"

/** Shrink a memory block allocated with x_malloc.
 *
 *  @param addr
 *  @param newsize
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_mshrink(void *addr, long newsize, short *global_aes)
{
	AES_PARAMS(0x7188,2,1,1,0);

	aes_intin_long(0) = newsize;
	aes_addrin[0] = (long)addr;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
