/*
 *  $Id$
 */

#include "gem_aesP.h"

/** suspends the application until a valid message that the
 *  application is interested in occurs.
 *
 *  @param em_i see mt_evnt_multi()
 *  @param msg see mt_evnt_mesag()
 *  @param em_o see mt_evnt_multi()
 *  @param global_aes global AES array
 *
 *  @return a bit mask of which events actually happened as in events.
 *          This may be one or more events and your application should
 *          be prepared to handle each.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  For detailed description consult the mt_evnt_multi() documentation.
 *
 */

short
mt_evnt_multi_fast (const EVMULT_IN * em_i, short msg[], EVMULT_OUT * em_o, short *global_aes)
{
	AES_PARAMS(25,16,7,1,0);

	aes_params.intin = (const short*)em_i;				/* input integer array */
	aes_params.intout = (short*)em_o;					/* output integer array */

	aes_addrin[0] = (long)msg;

	AES_TRAP(aes_params);

	return em_o->emo_events;
}

#ifdef evnt_multi_fast
#undef evnt_multi_fast
#endif
short
evnt_multi_fast (const EVMULT_IN * em_i, short msg[], EVMULT_OUT * em_o)
{
	return(mt_evnt_multi_fast(em_i,msg,em_o,aes_global));
}
