/*
 *  $Id$
 */

#include "gem_aesP.h"

/** sets various window attributes, only available in XaAES kernel module
 *  versions compiled on November 8 2004 or newer.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change
 *  @param s a rectange (which sets windows new coordinates)
 *  @param r a rectangle (which is filled in with the true coordinates of
 *         the window, as if wind_get() was used)
 *  @param global_aes global AES array
 *
 *  see mt_wind_set() documentation for more details
 */

short
mt_wind_xset_grect(short WindowHandle, short What, const GRECT *s, GRECT *r, short *global_aes)
{
	AES_PARAMS(105,6,5,0,0);
	aes_intin[0]			= WindowHandle;
	aes_intin[1]			= What;
	*(GRECT *)(aes_intin + 2) = *s;
	AES_TRAP(aes_params);

	*r = *(GRECT *)(aes_intout + 1);
	return (aes_intout[0]);
}
