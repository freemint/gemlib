/*
 *  $Id$
 */

#include "gem_aesP.h"

/** sets various window attributes.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change and the meanings of
 *         parameters \p W1 to \p W4
 *  @param W1 see hereafter
 *  @param W2 see hereafter
 *  @param W3 see hereafter
 *  @param W4 see hereafter<pre>
Name             mode  Meaning

WF_NAME           2    This mode passes a pointer to
                       a character string containing the
                       new title of the window. \p W1
                       contains the high WORD of the
                       pointer and \p W2 contains the low
                       WORD.

WF_INFO           3    This mode passes a pointer to
                       a character string containing the
                       new information line of the window.
                       \p W1 contains the high WORD of the
                       pointer, \p W2 contains the low
                       WORD.

WF_CURRXYWH       5    \p W1, \p W2, \p W3 and \p W4
                       specify the x, y, w, and h of the
                       new coordinates of the full extent
                       of the window.

WF_HSLIDE         8    \p W1 specifies the new position of
                       the horizontal slider between 1 and
                       1000. A value of 1 indicates that
                       the slider is in its leftmost
                       position.

WF_VSLIDE         9    \p W1 specifies the new position of
                       the vertical slider between 1 and
                       1000. A value of 1 indicates that
                       the slider is in its uppermost
                       position.

WF_TOP            10   \p WindowHandle specifies the window
                       handle of the window to top (parameter
					   \p W1 is unused !). Note that if
                       multiple calls of mt_wind_set( WF_TOP,
                       ... ) are made without releasing
                       control to the AES (which allows the
                       window to actually be topped), only
                       the most recent window specified
                       will actually change position.

WF_NEWDESK        14   This mode specifies a pointer to an
                       OBJECT tree which is redrawn
                       automatically by the desktop as the
                       background. \p W1 contains the high
                       WORD of the pointer and \p W2
                       contains the low WORD. To reset the
                       desktop background to the default,
                       specify \p W1 and \p W2 as 0.

WF_HSLSIZE        15   \p W1 defines the size of the
                       current slider relative to the size
                       of the scroll bar as a value from 1
                       to 1000. A value of 1000 indicates
                       that the slider is at its maximum
                       size.

WF_VSLSIZE        16   \p W1 defines the size of the
                       current slider relative to the size
                       of the scroll bar as a value from 1
                       to 1000. A value of 1000 indicates
                       that the slider is at its maximum
                       size.

WF_COLOR          18   This mode sets the current color of
                       the window widget specified on entry
                       in \p W1. Valid window widget
                       indexes are as follows (W_SMALLER is
                       only valid as of AES 4.1):

                       parm1     Value ob_type
                       W_BOX       0   IBOX
                       W_TITLE     1   BOX
                       W_CLOSER    2   BOXCHAR
                       W_NAME      3   BOXTEXT
                       W_FULLER    4   BOXCHAR
                       W_INFO      5   BOXTEXT
                       W_DATA      6   IBOX
                       W_WORK      7   IBOX
                       W_SIZER     8   BOXCHAR
                       W_VBAR      9   BOX
                       W_UPARROW  10   BOXCHAR
                       W_DNARROW  11   BOXCHAR
                       W_VSLIDE   12   BOX
                       W_VELEV    13   BOX
                       W_HBAR     14   BOX
                       W_LFARROW  15   BOXCHAR
                       W_RTARROW  16   BOXCHAR
                       W_HSLIDE   17   BOX
                       W_HELEV    18   BOX
                       W_SMALLER  19   BOXCHAR

                       The ob_spec field of the object
                       (containing the color information)
                       while the window is on top is
                       defined in \p W2. The ob_spec field
                       for the object while the window is
                       not on top is defined in \p W3.
                       This mode is only valid as of AES
                       version 0x0300.

WF_DCOLOR         19   This mode sets the default color of
                       newly created windows as with
                       WF_COLOR above. This mode only works
                       as of AES version 0x0300. As of AES
                       version 4.1, this mode causes all
                       currently displayed windows which
                       have not had their color explicitly
                       set with WF_COLOR to be changed.

WF_BEVENT         24   \p W1, \p W2, \p W3 and \p W4 are
                       each interpreted as bit arrays whose
                       bits indicate supported window
                       features. Currently only one bit is
                       supported. If bit 0 (B_UNTOPPABLE)
                       of \p W1 is set, the window will be
                       set to be 'un-toppable' and it will
                       never receive WM_TOPPED messages,
                       only button clicks. This mode is only
                       available as of AES versions 4.0.

WF_BOTTOM         25   This mode will place the specified
                       window at the bottom of the window
                       list (if there is more than one
                       window) and top the new window on
                       the top of the list. This mode is
                       only available as of AES version
                       4.0.

WF_ICONIFY        26   This mode iconifies the specified
                       window to the X, Y, width, and
                       height coordinates given in \p W1,
                       \p W2, \p W3, and \p W4
                       respectively. Normally, this happens
                       as the result of receiving
                       a WM_ICONIFY message. This mode is
                       only available as of AES
                       version 4.1.

WF_UNICONIFY      27   This mode uniconifies the window
                       specified, returning it to its
                       original X, Y, width, and height as
                       specified in \p W1, \p W2, \p W3,
					   and \p W4 respectively. Normally,
                       this happens as the result of
                       receiving a WM_UNICONIFY
                       message. This mode is only available
                       as of AES version 4.1.

WF_UNICONIFYXYWH  28   This mode sets the X, Y, width, and
                       height that will be transmitted to
                       the window with the next
                       WM_UNICONIFY message that targets
                       it. This call is used when a window
                       is opened in an iconified state to
                       give the OS a method of positioning
                       it when it is uniconified. This mode
                       is only available as of AES
                       version 4.1.

WF_TOOLBAR        30   This mode attaches a toolbar to the
                       specified window. \p W1 and \p W2
                       contain the high and low WORD of the
                       address of the toolbar OBJECT tree
                       respectively. \p W3 and \p W4 are
                       unused. Set \p W1 and \p W2 to 0 to
                       remove a toolbar.
                       WF_TOOLBAR is available as of AES 4.10.
					
WF_WIDGETS        200  Sets the actual positions of the slider
                       widgets (W_UPARROW, W_DNARROW, and so on)
					   of the window with the handle 'wi_ghandle'.
					   The parameters wi_gw1 and wi_gw2 are the
					   vertical elements of type rightwidget, the
                       parameters wi_gw3 and wi_gw4 are the
					   horizontal elements of type bottomwidgets.
					   wi_g1 is the top, wi_gw2 the bottom widget
					   of the vertical slider, wi_g3 the left, 
					   wi_g4 the right widget of the horizotal
					   slider.					   
					   </pre>
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_get()
 *
 */
 
short 
mt_wind_set (short WindowHandle, short What,
             short W1, short W2, short W3, short W4, short *global_aes)
{
	short *ptr;

	AES_PARAMS(105,6,1,0,0);

	ptr = aes_intin;
	*(ptr ++) = WindowHandle;							/* aes_intin[0] */
	*(ptr ++) = What;									/* aes_intin[1] */
	*(ptr ++) = W1; 								    /* aes_intin[2] */
	*(ptr ++) = W2; 								    /* aes_intin[3] */
	*(ptr ++) = W3; 								    /* aes_intin[4] */
	*(ptr ++) = W4; 								    /* aes_intin[5] */

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
