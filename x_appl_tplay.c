#include "gem_aesP.h"
#include "mt_gemx.h"

/** plays back events originally recorded with mt_x_appl_trecord().
 *
 *  @param mem is a pointer to an array of ::EVNTREC structures (see
 *         mt_appl_trecord())
 *  @param num indicates the number of ::EVNTREC's to play back.
 *  @param scale indicates on a scale of 1 to 10000 how fast the AES
 *         will attempt to play back your recording.
 *         The "original" doc
 *         says that the normal speed is 100 (200 = twice speeder,
 *         50 = twice slower... it's linear), but in most cases, 4 shall
 *         be used for normal speed (8=twice speeder, 2=twice slower..).
 *         See the important note
 *         below to know what's the right value for you.
 *  @param mode
 *  @param global_aes global AES array
 *
 *  @return always returns 1 meaning no error occurred.
 *
 *  @since Geneva
 *
 *  @sa mt_x_appl_trecord()
 *
 */

short
mt_x_appl_tplay(void *mem, short num, short scale, short mode, short *global_aes)
{
	AES_PARAMS(14,3,1,1,0);

	aes_intin[0]  = num;
	aes_intin[1]  = scale;
	aes_intin[2]  = mode;
	aes_addrin[0] = (long)mem;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
