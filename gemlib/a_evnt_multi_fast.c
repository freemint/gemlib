#include "gem_aesP.h"


short
evnt_multi_fast (const EVMULT_IN * em_i, short MesagBuf[], EVMULT_OUT * em_o)
{
	aes_params.intin  = (const short*)em_i;
	aes_params.intout = (short*)em_o;
	aes_addrin[0]     = (long)MesagBuf;
	
	AES_TRAP (aes_params, 25, 16,7,1,0);

	aes_params.intin  = aes_intin;
	aes_params.intout = aes_intout;
	
	return em_o->emo_events;
}
