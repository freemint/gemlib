/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Draws the Non-Client-Area (window widgets) of a window and checks the
 *  list of rectangles of the window specified.
 *
 *  @param whandle specifies the handle of the window to redraw
 *  @param startob index of the start object
 *  @param global_aes global AES array
 *
 *  @return a 0 if an error occurred or non-zero otherwise.
 *
 *  @since ???
 *
 *  @note This function is normaly not interesting for applications.
 *        The function is used by the screen manager for redrawing the
 *        window objects.
 *
 */

short 
mt_wind_draw (short whandle, short startob, short *global_aes)
{
	AES_PARAMS(99,2,1,0,0);

	aes_intin[0] = whandle;
	aes_intin[1] = startob;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
