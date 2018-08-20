#include "gem_aesP.h"

short 
mt_wind_set_int (short WindowHandle, short What, short W1, short *global_aes)
{
	short *ptr;

	AES_PARAMS(105,6,1,0,0);

	ptr = aes_intin;
	*(ptr ++) = WindowHandle;							/* aes_intin[0] */
	*(ptr ++) = What;									/* aes_intin[1] */
	*(ptr ++) = W1; 								    /* aes_intin[2] */
	*(ptr ++) = 0; 									    /* aes_intin[3] */
	*(ptr ++) = 0; 									    /* aes_intin[4] */
	*(ptr ++) = 0; 									    /* aes_intin[5] */

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
