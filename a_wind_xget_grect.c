/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns various information about a window.
 *
 *  @param WindowHandle specifies the handle of the window to return
 *         information about (0 is the desktop window)
 *  @param What specifies the information to return and the values
 *         placed into \a r.
 *  @param clip additional information about the request. For now, this
 *         information is only taken into account for command
 *         #WF_FIRSTAREAXYWH. In that case, \a clip is a clipping area, and the
 *         AES may optimize the list of rectangles returned by #WF_FIRSTAREAXYWH
 *         and #WF_NEXTXYWH.
 *  @param r value returned, see mt_wind_get()
 *  @param global_aes global AES array
 *
 *  see mt_wind_get() documentation for more details.
 */

short 
mt_wind_xget_grect(short WindowHandle, short What, const GRECT *clip, GRECT *r, short *global_aes)
{
	AES_PARAMS(104,6,5,0,0);
                    
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	
	*(GRECT*)(aes_intin + 2) = *clip;
	
	AES_TRAP(aes_params);

	*r = *(GRECT*)(aes_intout +1);
	
	return (aes_intout[0]);
}
