#include "gem_aesP.h"
#include "mt_gemx.h"

/** records AES events for later playback.
 *
 *  @param mem points to an array of \a Count ::EVNTREC structures
 *  @param count dimension of the array of ::EVNTREC structures into which
 *         the AES will record events
 *  @param cancel
 *  @param mode
 *  @param global_aes global AES array
 *
 *  @return addreturns the number of events actually recorded.
 *
 *  @since Geneva
 *
 *  @sa mt_x_appl_tplay()
 *
 */

short
mt_x_appl_trecord(void *mem, short count, KEYCODE *cancel, short mode, short *global_aes)
{
	AES_PARAMS(15,2,1,2,0);

	aes_intin[0]  = count;
	aes_intin[1]  = mode;
	aes_addrin[0] = (long)mem;
	aes_addrin[1] = (long)cancel;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
