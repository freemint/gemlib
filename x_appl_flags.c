#include "gem_aesP.h"
#include "mt_gemx.h"

/** controls the execution flags that are used when determining how an application gets run
 *
 *  @param getset 
 *  @param index
 *  @param flags
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_appl_flags(short getset, short index, APPFLAGS *flags, short *global_aes)
{
	AES_PARAMS(0x7100,2,1,1,0);

	aes_intin[0] = getset;
	aes_intin[1] = index;
	aes_addrin[0] = (long)flags;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
