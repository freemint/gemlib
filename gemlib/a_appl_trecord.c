/*
 *  $Id$
 */

#include "gem_aesP.h"

/** records AES events for later playback.
 *
 *  @param Mem points to an array of \p Count EVNTREC structures
 *  @param Count dimension of the array of EVNTREC structures into which
 *         the AES will record events as indicated here:<pre>
typedef struct pEvntrec
{
	WORD ap_event;
	LONG ap_value;
} EVNTREC;</pre>
 *         ap_event defines the required interpretation of ap_value
 *         as follows:<pre>
Name		 ap_event Event 	ap_value

APPEVNT_TIMER	 0    Timer 	Elapsed Time (in
								milliseconds)

APPEVNT_BUTTON   1    Button	low word  = state
											(1 = down)
								high word = # of clicks

APPEVNT_MOUSE	 2    Mouse 	low word  = X pos
								high word = Y pos

APPEVNT_KEYBOARD 3    Keyboard  bits 0-7:	ASCII code
								bits 8-15:  scan code
								bits 16-31: shift key
								state</pre>
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
 */

short 
mt_appl_trecord(void *Mem, short Count, short *global_aes)
{
	AES_PARAMS(15,1,1,1,0);
                    
	aes_intin[0]  = Count;
	aes_addrin[0] = (long)Mem;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_trecord
#undef appl_trecord
#endif
short 
appl_trecord(void *Mem, short Count)
{
	return(mt_appl_trecord(Mem, Count, aes_global));
}

