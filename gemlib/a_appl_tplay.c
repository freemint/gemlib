/*
 *  $Id$
 */

#include "gem_aesP.h"

/** plays back events originally recorded with mt_appl_trecord().
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
 *
 *  @note The mt_appl_trecord() function is bugged and stores a count of
 *        a 200Hz timer in EVNTREC::ap_value for #APPEVNT_TIMER events,
 *        instead of a number of millisecondes. So, there is a coefficient
 *        of 5 between the value stored by mt_appl_trecord() and the value
 *        expected by mt_appl_tplay().
 *        The mt_appl_tplay() function takes care of that and adds a coefficient
 *        of 5 for #APPEVNT_TIMER event... but this has been implemented the
 *        wrong way ! and now the coefficient between "time" recorded by 
 *        mt_appl_trecord() and "time" played by mt_appl_tplay() is 25.
 *        That's the reason why the right value for the scale parameter is
 *        100/25=4 for normal speed, 200/25=8 for twice speeder replay,
 *        50/25=2 for twice slower replay...
 *
 *  @note About the previous note: this story is just an hypothesis to explain 
 *        the fact: the official doc says 100=normal speed but experiences have
 *        proven that 4=normal speed (Magic, tos).
 *
 *  @note Geneva seems to follows exactly the original doc. So, events recorded
 *        by Geneva should be played by geneva with scale=100 for normal speed;
 *        and event recorded by magic should be replayed by geneva with scale=500 for
 *        normal speed...
 *
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
