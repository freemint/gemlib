/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns various information about a window.
 *
 *  @param WindowHandle specifies the handle of the window to return
 *         information about (0 is the desktop window)
 *  @param What specifies the information to return and the values
 *         placed into \p r.
 *  @param r
 *  @param global_aes global AES array
 *
 *  see mt_wind_get() documentation for more details.
 */

short 
mt_wind_get_grect(short WindowHandle, short What, GRECT *r, short *global_aes)
{
	AES_PARAMS(104,2,5,0,0);
                    
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	
	AES_TRAP(aes_params);

	*r = *(GRECT*)(aes_intout +1);
	
	return (aes_intout[0]);
}
