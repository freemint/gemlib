#include "gem_aesP.h"

/** opens the window specified.
 *
 *  @param WindowHandle specifies the handle of the window to open as
           returned by mt_wind_create()
 *  @param Wx x-position of the rectangle
 *  @param Wy y-position of the rectangle
 *  @param Ww width of the rectangle
 *  @param Wh height of the rectangle into which the rectangle should be displayed.
 *  @param global_aes global AES array
 *
 *  @return a 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_close(), mt_wind_create(), mt_wind_delete()
 *
 *  This call will also trigger a #WM_REDRAW message which
 *  encompasses the work area of the window so applications
 *  should not initially render the work area, rather, wait for
 *  the message.
 *
 */

short 
mt_wind_open (short WindowHandle, short Wx, short Wy, short Ww, short Wh, short *global_aes)
{
	short *ptr;
	
	AES_PARAMS(101,5,1,0,0);

	ptr = aes_intin;
	*(ptr ++) = WindowHandle;							/* aes_intin[0] */
	*(ptr ++) = Wx;										/* aes_intin[1] */
	*(ptr ++) = Wy;										/* aes_intin[2] */
	*(ptr ++) = Ww;										/* aes_intin[3] */
	*(ptr)    = Wh;										/* aes_intin[4] */

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
