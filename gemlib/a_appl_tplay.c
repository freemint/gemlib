/*
 *  $Id$
 */

#include "gem_aesP.h"

/** plays back events originally recorded with mt_appl_trecord().
 *
 *  @param mem is a pointer to an array of EVNTREC structures (see
 *         appl_trecord())
 *  @param num indicates the number of EVNTREC's to play back.
 *  @param scale indicates on a scale of 1 to 10000 how fast the AES
 *         will attempt to play back your recording as follows:
 *         - 100 : recorded speed
 *         - 200 : twice recorded speed
 *         - 50  : half of the recorded speed
 *         - Other values will respond accordingly.
 *  @param global_aes global AES array
 *
 *  @return always returns 1 meaning no error occurred.
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_trecord()
 *
 *  This function does not work correctly on AES versions less
 *  than 1.40 without a patch program available from Atari
 *  Corp..
 */

short
mt_appl_tplay(void *mem, short num, short scale, short *global_aes)
{
	AES_PARAMS(14,2,1,1,0);

	aes_intin[0]  = num;
	aes_intin[1]  = scale;
	aes_addrin[0] = (long)mem;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
