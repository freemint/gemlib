/*
 *  $Id$
 */

#include "gem_aesP.h"

/** opens the window specified.
 *
 *  @param WindowHandle specifies the handle of the window to open as
 *         returned by mt_wind_create()
 *  @param r the rectangle into which the rectangle should be displayed.
 *  @param global_aes global AES array
 *
 *  see mt_wind_open() documentation for more details.
 */

short 
mt_wind_open_grect(short WindowHandle, const GRECT *r, short *global_aes)
{
	AES_PARAMS(101,5,1,0,0);
                    
	aes_intin[0] = WindowHandle;
	*(GRECT*)(aes_intin +1) = *r;
	
	AES_TRAP(aes_params);

	return aes_intout[0];
}
