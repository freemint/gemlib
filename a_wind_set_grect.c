/*
 *  $Id$
 */

#include "gem_aesP.h"

/** sets various window attributes.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change
 *  @param r a rectangle
 *  @param global_aes global AES array
 *
 *  see mt_wind_set() documentation for more details
 *  
 *  the fields x, y, w and h of \a r are respectively sent in place of the 
 *  parameters \a w1, \a w2, \a w3 and \a w4 of mt_wind_set().
 */

short 
mt_wind_set_grect(short WindowHandle, short What, const GRECT *r, short *global_aes)
{
	AES_PARAMS(105,6,1,0,0);

	aes_intin[0]			= WindowHandle;
	aes_intin[1]			= What;
	*(GRECT*)(aes_intin +2) = *r;
	
	AES_TRAP(aes_params);
	
	return (aes_intout[0]);

}
