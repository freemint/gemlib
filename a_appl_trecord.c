#include "gem_aesP.h"

/** records AES events for later playback.
 *
 *  @param mem points to an array of \a Count ::EVNTREC structures
 *  @param count dimension of the array of ::EVNTREC structures into which
 *         the AES will record events
 *  @param global_aes global AES array
 *
 *  @return addreturns the number of events actually recorded.
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_tplay()
 *
 *  This function does not work correctly on AES versions less
 *  than 1.40 without a patch program available from Atari
 *  Corp.
 *
 *  @note \p ap_value seems to have words swapped (#APPEVNT_MOUSE: X pos is in the high
 *  word and Y pos is in the low word).
 *
 *  @note Warning: the "elapsed time" unit should be milliseconds but it seems that most
 *       of the AES fill this value with a count of the 200Hz timer... but this is
 *       taken into account by a dirty and bugged workaround in mt_appl_tplay().
 *
 *  @note It seems that Geneva follows the original doc and stores the "elapsed time"
 *        in milliseconds.
 */

short
mt_appl_trecord(void *mem, short count, short *global_aes)
{
	AES_PARAMS(15,1,1,1,0);

	aes_intin[0]  = count;
	aes_addrin[0] = (long)mem;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
