#include "gem_aesP.h"


short
evnt_mesag (short MesagBuf[])
{
	aes_addrin[0] = (long)MesagBuf;

	AES_TRAP (aes_params, 23, 0,1,1,0);

	return aes_intout[0];
}
