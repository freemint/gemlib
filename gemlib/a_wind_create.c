/*
 *  $Id$
 */

#include "gem_aesP.h"

/** initializes a new window structure and allocates any necessary memory.
 *
 *  @param Parts is a bit array whose elements determine the presence of
 *         any 'widgets' on the window as follows:
 *         - #NAME     (0x01)     Window has a title bar.
 *         - #CLOSER   (0x02)     Window has a close box.
 *         - #FULLER   (0x04)     Window has a fuller box.
 *         - #MOVER    (0x08)     Window may be moved by the user.
 *         - #INFO     (0x10)     Window has an information line.
 *         - #SIZER    (0x20)     Window has a sizer box.
 *         - #UPARROW  (0x40)     Window has an up arrow.
 *         - #DNARROW  (0x80)     Window has a down arrow.
 *         - #VSLIDE   (0x100)    Window has a vertical slider.
 *         - #LFARROW  (0x200)    Window has a left arrow.
 *         - #RTARROW  (0x400)    Window has a right arrow.
 *         - #HSLIDE   (0x800)    Window has a horizontal slider.
 *         - #HOTCLOSEBOX  (0x1000)   Window has "hot close box" box.
 *         - #MENUBAR  (0x1000)   Window has a menu bar.
 *         - #BACKDROP (0x2000)   Window has a backdrop box.
 *         - #SMALLER  (0x4000)   Window has an iconifier.
 *         - #BORDER   (0x8000)   Window has border-resize capability (XaAES).
 *         The parameter \a Parts is created by OR'ing together any desired
 *         elements.
 *  @param Wx X-position of the maximum extents of the window.
 *  @param Wy Y-position of the maximum extents of the window.
 *  @param Ww Width of the maximum extents of the window.
 *  @param Wh Height of the maximum extents of the window.\n
 *         Normally this is the entire screen area minus the menu bar
 *         (to find this area use mt_wind_get() with a parameter of
 *         #WF_WORKXYWH ). The area may be smaller to bound the window
 *         to a particular size and location.
 *  @param global_aes global AES array
 *
 *  @return a window handle if successful or
 *          a negative number if it was unable to create the window.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_open(), mt_wind_close(), mt_wind_delete()
 *
 *  The #SMALLER gadget is only available as of AES version 4.1.
 *
 *  The #BORDER gadget is only available in XaAES kernel module
 *  versions compiled after November 8, 2004.
 *
 *  A window is not actually displayed on screen with this call,
 *  you need to call mt_wind_open() to do that.
 *
 *  The desktop was limited to four windows. The AES actually
 *  allowed seven windows. As of MultiTOS the number of open
 *  windows is limited only by memory and the capabilities of an
 *  application. You should ensure that your application calls
 *  a mt_wind_delete() for each mt_wind_create(), otherwise memory may
 *  not be deallocated when your application exits.
 *
 */
 
short 
mt_wind_create (short Parts, short Wx, short Wy, short Ww, short Wh, short *global_aes)
{
	short *ptr;
	
	AES_PARAMS(100,5,1,0,0);
           
	ptr = aes_intin;
	*(ptr ++) = Parts;				 /* aes_intin[0] */
	*(ptr ++) = Wx;					 /* aes_intin[1] */
	*(ptr ++) = Wy;					 /* aes_intin[2] */
	*(ptr ++) = Ww;					 /* aes_intin[3] */
	*(ptr)    = Wh;					 /* aes_intin[4] */

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
