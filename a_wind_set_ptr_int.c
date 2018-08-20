#include "gem_aesP.h"

short 
mt_wind_set_ptr_int (short WindowHandle, short What, void *v, short W3, short *global_aes)
{
	AES_PARAMS(105,6,1,0,0);

	aes_intin[0]                  = WindowHandle;
	aes_intin[1]                  = What;
	*(void**)(aes_intin +2) = v;
	aes_intin[4]                  = W3;
	aes_intin[5]                  = 0;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
