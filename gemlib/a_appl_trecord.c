/*
 *  $Id$
 */

#include "gem_aesP.h"

/** records AES events for later playback.
 *
 *  @param mem points to an array of \p Count EVNTREC structures
 *  @param count dimension of the array of EVNTREC structures into which
 *         the AES will record events as indicated here: \n
 *         typedef struct pEvntrec \n
 *         { \n
 *         	LONG ap_event; \n
 *         	LONG ap_value; \n
 *         } EVNTREC; \n
 *         ap_event defines the required interpretation of ap_value
 *         as follows:
 *         - ap_event : APPEVNT_TIMER (0) \n
 *           ap_value : Elapsed Time (in milliseconds)
 *         - ap_event : APPEVNT_BUTTON (1) \n
 *           ap_value : low word  = state (1 = down), high word = # of clicks
 *         - ap_event : APPEVNT_MOUSE (2) \n
 *           ap_value : low word  = X pos, high word = Y pos
 *         - ap_event : APPEVNT_KEYBOARD (3) \n
 *           ap_value : bits 0-7 = ASCII code, bits 8-15 = scan code, bits 16-31 = shift key
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
 *  @note \p ap_value seems to have words swapped (APPEVNT_MOUSE: X pos is in the high
 *  word and Y pos is in the low word).
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
