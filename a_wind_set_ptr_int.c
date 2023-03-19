#include "gem_aesP.h"

/** sets various window attributes.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change
 *  @param v a pointer
 *  @param W3 see hereafter
 *  @param global_aes global AES array
 *
 *  see mt_wind_set() documentation for more details
 *  
 *  the \a v pointer (32 bits) is sent in place of the two first parameters
 *  \a w1 (most significant word of \a str) and \a w2 (less significant word
 *  of \a str) of mt_wind_set(). The \a W3 value (16 bits) is sent in place of 
 *  third parameter \a w3 of mt_wind_set().Parameter \a w4 of mt_wind_set() is
 *  undefined.
 */

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
