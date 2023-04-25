#include "gem_aesP.h"
#include "mt_gemx.h"

/** Obtain pathname of the clipboard.
 *
 *  @param deleteit
 *  @param out
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_scrp_get(char *out, short deleteit, short *global_aes)
{
	AES_PARAMS(0x7160,1,1,1,0);

	aes_intin[0] = deleteit;
	aes_addrin[0] = (long)out;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
