#include "gem_aesP.h"
#include "mt_gemx.h"

/** Save a program's own settings, or Geneva's settings, to GENEVA.CNF.
 *
 *  @param mode
 *  @param buf
 *  @param global_aes global AES array
 *
 *  @return 1 if no error has occurred or a value<>0 otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_shel_put(short mode, const char *buf, short *global_aes)
{
	AES_PARAMS(0x7182,1,1,1,0);

	aes_intin[0] = mode;
	aes_addrin[0] = (long)buf;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
