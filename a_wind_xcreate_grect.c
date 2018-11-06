#include "gem_aesP.h"

/** initializes a new window structure and allocates any necessary memory.
 *
 *  @param Parts is a bit array whose elements determine the presence of
 *         any 'widgets' on the window.
 *  @param r specify the maximum extents of the window.
 *  @param OutR Corrected maximum extents of window, if 'r' exceeded it.
 *  @param global_aes global AES array
 *
 *  see mt_wind_xcreate() documentation for more details
 */

short 
mt_wind_xcreate_grect(short Parts, const GRECT *r, GRECT *OutR, short *global_aes)
{
	AES_PARAMS(100,5,5,0,0);
                    
	aes_intin[0] = Parts;
	*(GRECT*)(aes_intin +1) = *r;

	AES_TRAP(aes_params);

	*OutR = *(GRECT *)(aes_intout + 1);

	return aes_intout[0];
}
