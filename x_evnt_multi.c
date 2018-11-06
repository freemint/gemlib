#include "gem_aesP.h"
#include "mt_gemx.h"

/** see mt_evnt_multi().
 *
 *  @param evtypes see mt_evnt_multi()
 *  @param nclicks see mt_evnt_multi()
 *  @param bmask see mt_evnt_multi()
 *  @param bstate see mt_evnt_multi()
 *  @param m1 see mt_evnt_multi()
 *  @param m2 see mt_evnt_multi()
 *  @param ms see mt_evnt_multi()
 *  @param event see mt_evnt_multi()
 *  @param global_aes global AES array
 *
 *  @return  see mt_evnt_multi()
 *
 *  @since  see mt_evnt_multi()
 *  
 */

void 
mt_EVNT_multi( short evtypes, short nclicks, short bmask, short bstate,
			   const MOBLK *m1, const MOBLK *m2, unsigned long ms, EVNT *event, short *global_aes )
{
	short *ev;
	short *intout;
	MOBLK *m;
	
	AES_PARAMS(25,16,7,1,0);

	aes_intin[0] = evtypes;
	aes_intin[1] = nclicks;
	aes_intin[2] = bmask;
	aes_intin[3] = bstate;

	if	( evtypes & MU_M1 )
	{
		m = (MOBLK *)( aes_intin + 4 );
		*m = *m1;
	}

	if	( evtypes & MU_M2 )
	{
		m = (MOBLK *)( aes_intin + 9 );
		*m = *m2;
	}

	aes_intin[14] = ms;
	aes_intin[15] = ms >> 16;

	aes_addrin[0] = (long)event->msg;

	AES_TRAP(aes_params);

	ev = (short *) event;
	intout = aes_intout;
	
	*ev++ = *intout++;						/* mwhich */
	*ev++ = *intout++;						/* mx */
	*ev++ = *intout++;						/* my */
	*ev++ = *intout++;						/* mbutton */
	*ev++ = *intout++;						/* kstate */
	*ev++ = *intout++;						/* key */
	*ev++ = *intout++;						/* mclicks */
}
