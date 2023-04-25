#include "gem_aesP.h"
#include "mt_gemx.h"

/** Extended wind_create().
 *
 *  @param kind is a bit array whose elements determine the presence of
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
 *         .
 *         The parameter \a Parts is created by OR'ing together any desired
 *         elements.
 *  @param xkind Extended window type
 *  @param wx X-position of the maximum extents of the window.
 *  @param wy Y-position of the maximum extents of the window.
 *  @param ww Width of the maximum extents of the window.
 *  @param wh Height of the maximum extents of the window.\n
 *         Normally this is the entire screen area minus the menu bar
 *         (to find this area use mt_wind_get() with a parameter of
 *         #WF_WORKXYWH ). The area may be smaller to bound the window
 *         to a particular size and location.
 *  @param global_aes global AES array
 *
 *  @return a window handle if successful or
 *          a negative number if it was unable to create the window.
 *
 *  @since Geneva
 *
 */

short
mt_x_wind_create(short kind, short xkind, short wx, short wy, short ww, short wh, short *global_aes)
{
	AES_PARAMS(0x7153,6,1,0,0);

	aes_intin[0] = kind;
	aes_intin[1] = xkind;
	aes_intin[2] = wx;
	aes_intin[3] = wy;
	aes_intin[4] = ww;
	aes_intin[5] = wh;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
