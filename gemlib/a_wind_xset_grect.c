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
 *  @param s is a rectangle containing coordinates for WF_CURRXYWH,
 *         WF_PREVXYWH, and WF_FULLXYWH modes.
 *         wind_xset_grect(handle, WF_CURRXYWH, (const GRECT *)s, (GRECT *)r);
 *         will set the coordinates of the window, just like
 *         wind_set_grect(handle, WF_CURRXYWH, (const GRECT *)r);
 *         but will return the coordinates actually set in 'r'. This eliminates
 *         the need to do wind_get_grect(..) to fetch the newly set coordinates.
 *         Refer to the XaAES documentation for more information about the
 *         extended wind_set() modes
 *  @param r actual coordinates returned
 *  @param global_aes global AES array
 *
 *  see mt_wind_set() documentation for more details.
 */

short 
mt_wind_xset_grect(short WindowHandle, short What, const GRECT *s, GRECT *r, short *global_aes)
{
	AES_PARAMS(104,6,5,0,0);
                    
	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;
	
	*(GRECT*)(aes_intin + 2) = *s;
	
	AES_TRAP(aes_params);

	*r = *(GRECT*)(aes_intout +1);
	
	return (aes_intout[0]);
}
