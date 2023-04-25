#include "gem_aesP.h"
#include "mt_gemx.h"

/** Allocate memory from Geneva. 
 *
 *  @param addr
 *  @param size
 *  @param global_aes global AES array
 *
 *  @since Geneva
 *
 */

void
mt_x_malloc(void **addr, long size, short *global_aes)
{
	AES_PARAMS(0x7186,1,1,2,0);

	aes_intin_long(0) = size;
	aes_addrin[0] = (long)addr;

	AES_TRAP(aes_params);
}
