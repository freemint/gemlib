#include "gem_aesP.h"


short
evnt_timer (unsigned long Interval)
{
	unsigned short *i = (unsigned short *) &Interval;

	aes_intin[0] = i[1];
	aes_intin[1] = i[0];
	
	AES_TRAP (aes_params, 24, 2,1,0,0);
	
	return aes_intout[0];
}
