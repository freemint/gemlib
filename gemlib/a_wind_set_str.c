/*
 *  $Id$
 */

#include "gem_aesP.h"

/** sets various window attributes.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change
 *  @param str a string
 *  @param global_aes global AES array
 *
 *  see mt_wind_set() documentation for more details
 */

short 
mt_wind_set_str (short WindowHandle, short What, const char *str, short *global_aes)
{
	AES_PARAMS(105,6,1,0,0);

	aes_intin[0]                  = WindowHandle;
	aes_intin[1]                  = What;
	*(const char**)(aes_intin +2) = str;
	
	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
