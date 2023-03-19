#include "gem_aesP.h"

/** sets various window attributes.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change
 *  @param W1 see hereafter
 *  @param global_aes global AES array
 *
 *  see mt_wind_set() documentation for more details
 *  
 *  the \a W1 value (16 bits) is sent in place of the first parameter
 *  \a w1 of mt_wind_set(). Parameters \a w2, \a w3 and \a w4 of mt_wind_set()
 *  are undefined.
 */

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
