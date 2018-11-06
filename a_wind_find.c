#include "gem_aesP.h"

/** returns the handle of the window found at the given coordinates.
 *
 *  @param X specify the X-coordinate to search for a window at.
 *  @param Y specify the Y-coordinate to search for a window at.
 *  @param global_aes global AES array
 *
 *  @return the handle of the uppermost window
 *          found at location \a X, \a Y. If no window is found, the function
 *          returns 0 meaning the Desktop window.
 *
 *  @since All AES versions.
 *
 *  This function is useful for tracking the mouse pointer and
 *  changing its shape depending upon what window it falls
 *  over.
 *
 */
 
short 
mt_wind_find (short X, short Y, short *global_aes)
{
	AES_PARAMS(106,2,1,0,0);
                    
	aes_intin[0] = X;
	aes_intin[1] = Y;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
