/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns various information about a window.
 *
 *  @param WindowHandle specifies the handle of the window to return
 *         information about (0 is the desktop window)
 *  @param What specifies the information to return and the values
 *         placed into the WORDs pointed to by \p W1 to \p W4.
 *  @param W1 1st returned value \n
 *         [option CHECK_NULLPTR] W1 may be NULL
 *  @param W2 2nd returned value \n
 *         [option CHECK_NULLPTR] W2 may be NULL
 *  @param W3 3rd returned value \n
 *         [option CHECK_NULLPTR] W3 may be NULL
 *  @param W4 4th returned value \n
 *         [option CHECK_NULLPTR] W4 may be NULL
 *  @param global_aes global AES array
 *
 *  @return a 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions. WF_KIND, WF_NAME and WF_INFO since NAES (release?).
 *
 *  @sa mt_wind_set()
 *
<pre>
    Name         mode  Meaning

 	WF_KIND        1   \p W1 contains the actual window elements
	                   with N.AES or MagiC.
 
 	WF_NAME        2   Gets the actual title of the window
	                   and copies the title in the buffer 
					   with the address in \p W1.
 
 			           If the window has no title, the return
					   value of the function equals 0, the buffer
					   remains unchanged.
 
 			           Since a title may have a length of 128
					   chars, the buffer must be large enough!
 
 	WF_INFO        3   Gets the actual infoline of the window
	                   and copies the infoline in the buffer with
					   the address \p W1.
 
 					   If the window has no infoline, the return
					   value of the function equals 0, the buffer 
					   remains unchanged.
 
 					   Since an infoline may have a length of 128
					   chars, the buffer must be large enough!

    WF_WORKXYWH    4   \p W1, \p W2, \p W3 and \p W4 are
                       filled in with the x, y, w, and h of the
                       current coordinates of the window's work
                       area.

    WF_CURRXYWH    5   \p W1, \p W2, \p W3 and \p W4 are
                       filled in with the x, y, w, and h of the
                       current coordinates of the full extent
                       of the window.

    WF_PREVXYWH    6   \p W1, \p W2, \p W3 and \p W4 are
                       filled in with the x, y, w, and h of the
                       previous coordinates of the full extent
                       of the window prior to the last
                       mt_wind_set() call.

    WF_FULLXYWH    7   \p W1, \p W2, \p W3 and \p W4 are
                       filled in with the x, y, w, and h values
                       specified in the mt_wind_create() call.

    WF_HSLIDE      8   \p W1 is filled in with the current
                       position of the horizontal slider
                       between 0 and 1000. A value of one
                       indicates that the slider is in its
                       leftmost position.

    WF_VSLIDE      9   \p W1 is filled in with the current
                       position of the vertical slider between
                       0 and 1000. A value of one indicates
                       that the slider is in its uppermost
                       position.

    WF_TOP        10   \p W1 is filled in with the window
                       handle of the window currently on top.
                       As of AES version 4.0 (and when
                       mt_appl_getinfo() indicates), \p W2 is
                       filled in with the owners AES id, and
                       \p W3 is filled in with the handle of
                       the window directly below it.

    WF_FIRSTXYWH  11   \p W1, \p W2, \p W3 and \p W4 are
                       filled in with the x, y, w, and h of the
                       first AES rectangle in the window's
                       rectangle list. If \p W3 and \p W4 are
                       both 0, the window is completely
                       covered.

    WF_NEXTXYWH   12   \p W1, \p W2, \p W3 and \p W4 are
                       filled in with subsequent AES rectangles
                       for each time this function is called
                       until \p W3 and \p W4 are 0 to signify
                       the end of the list.

    WF_NEWDESK    14   As of AES versions 4.0 (and when
                       mt_appl_getinfo() indicates), this mode
                       returns a pointer to the current desktop
                       background OBJECT tree. \p W1 contains
                       the high WORD of the address and \p W2
                       contains the low WORD.

    WF_HSLSIZE    15   \p W1 contains the size of the current
                       slider relative to the size of the
                       scroll bar as a value from 0 to 1000.
                       A value of 1000 indicates that the
                       slider is at its maximum size.

    WF_VSLSIZE    16   \p W1 contains the size of the current
                       slider relative to the size of the
                       scroll bar as a value from 0 to 1000.
                       A value of 1000 indicates that the
                       slider is at its maximum size.

    WF_SCREEN     17   This mode returns a pointer to the
                       current AES menu/alert buffer and its
                       size. The pointer's high WORD is
                       returned in \p W1 and the pointer's low
                       WORD is returned in \p W2. The length of
                       the buffer is returned as a LONG with
                       the upper WORD being in \p W3 and the
                       lower WORD being in \p W4. Note that GEM
                       1.2 returns 0 in w and h by mistake.
                       The menu/alert buffer is used by the
                       AES to save the screen area hidden by
                       menus and alert boxes. It is not
                       recommended that applications use this
                       area as its usage is not guaranteed in
                       future versions of the OS.

    WF_COLOR      18   This mode gets the current color of the
                       window widget specified on entry to the
                       function in the WORD pointed to by
                       \p W1. Valid window widget indexes are
                       as follows (W_SMALLER is only valid as
                       of AES 4.1):

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

                       The ob_spec field (containing the
                       color information) used for the object

                       when not selected is returned in the
                       WORD pointed to by \p W2. The ob_spec
                       field used for the object when selected
                       is returned in \p W3.
                       This mode under mt_wind_get() is only
                       valid as of AES version 3.30. From AES
                       versions 4.0 and above, mt_appl_getinfo()
                       should be used to determine if this mode
                       is supported.

    WF_DCOLOR     19   This mode gets the default color of
                       newly created windows as with WF_COLOR
                       above. As above, this mode under
                       mt_wind_get() only works as of AES
                       version 3.30.
                       As of AES version 4.1, WF_DCOLOR
                       changes the color of open windows unless
                       they have had their colors explicitly
                       set with WF_COLOR.

    WF_OWNER      20   \p W1 is filled in with the AES id of
                       the owner of the specified window. \p W2
                       is filled in with its open status
                       (0 = closed, 1 = open). \p W3 is filled
                       in with the handle of the window directly
                       above it (in the window order list) and
                       \p W4 is filled in with the handle of
                       the window below it (likewise, in the
                       window order list).
                       This mode is only available as of AES
                       version 4.0 (and when indicated by
                       mt_appl_getinfo()).

    WF_BEVENT     24   \p W1, \p W2, \p W3 and \p W4 are each
                       interpreted as bit arrays whose bits
                       indicate supported window features.
                       Currently only one bit is supported. If
                       bit 0 of the value returned in \p W1 is
                       1, that window has been set to be
                       'un-toppable' and it will never receive
                       WM_TOPPED messages, only button clicks.
                       This mode is only available as of AES
                       version 4.0 (and when indicated by
                       mt_appl_getinfo() ).

    WF_BOTTOM     25   \p W1 will be filled in with the handle
                       of the window currently on the bottom of
                       the window list (it may actually be on
                       top if there is only one window). Note
                       also that this does not include the
                       desktop window.
                       This mode is only available as of AES
                       version 4.0 (and when indicated by
                       mt_appl_getinfo()).

    WF_ICONIFY    26   \p W1 will be filled in with 0 if the
                       window is not iconified or non-zero if
                       it is. \p W2 and \p W3 contain the width
                       and height of the icon. \p W4 is
                       unused.
                       This mode is only available as of AES
                       version 4.1 (and when indicated by
                       mt_appl_getinfo() ).

    WF_UNICONIFY  27   \p W1, \p W2, \p W3 and \p W4, are
                       filled in with the x, y, w, and h of the
                       original coordinates of the iconified
                       window.
                       This mode is only available as of AES
                       version 4.1 (and when indicated by
                       mt_appl_getinfo()).

    WF_TOOLBAR    30   \p W1 and \p W2 contain the high and low
                       WORD respectively of the pointer to the
                       current toolbar object tree (or NULL if
                       none).
                       This mode is only available as of AES
                       version 4.1.

    WF_FTOOLBAR   31   \p W1, \p W2, \p W3 and \p W4, are
                       filled in with the x, y, w, and h,
                       respectively of the first uncovered
                       rectangle of the toolbar region of the
                       window. If \p W3 and \p W4 are 0, the
                       toolbar is completely covered.
                       This mode is only available as of AES
                       version 4.1.

    WF_NTOOLBAR   32   \p W1, \p W2, \p W3 and \p W4, are
                       filled in with the x, y, w, and h,
                       respectively of subsequent uncovered
                       rectangles of the toolbar region. This
                       mode should be repeated to reveal
                       subsequent rectangles until \p W3 and
                       \p W4 are found to be 0.
                       This mode is only available as of AES
                       version 4.1.

    WF_WIDGETS    200  Gets the actual positions of the slider
                       widgets (W_UPARROW, W_DNARROW, and so on)
					   of the window with the handle 'wi_ghandle'.
					   The parameters wi_gw1 and wi_gw2 are the
					   vertical elements of type rightwidget, the
                       parameters wi_gw3 and wi_gw4 are the
					   horizontal elements of type bottomwidgets.
					   wi_g1 is the top, wi_gw2 the bottom widget
					   of the vertical slider, wi_g3 the left, 
					   wi_g4 the right widget of the horizotal
					   slider.	</pre>
				   
 *
 *  @note aes_intout[3,4] are initialized to 0 before the AES trap.
 *        It's usefull under NAES for WF_FIRST/NEXTXYWH since lot
 *        of programmers only check for w and h = 0, and not the
 *        return value.
 *
 */

short 
mt_wind_get (short WindowHandle, short What,
             short *W1, short *W2, short *W3, short *W4, short *global_aes)
{
	short *ptr;
	short aes_control[AES_CTRLMAX],
	      aes_intin[AES_INTINMAX],
		  aes_intout[AES_INTOUTMAX];
	long  aes_addrin[AES_ADDRINMAX], 
	      aes_addrout[AES_ADDROUTMAX];
	AESPB aes_params;

	aes_params.control = &aes_control[0];				/* AES Control Array */
	aes_params.global  = &global_aes[0];				/* AES Global Array */
	aes_params.intin   = &aes_intin[0];					/* input integer array */
	aes_params.intout  = &aes_intout[0];				/* output integer array */
	aes_params.addrin  = &aes_addrin[0];				/* input address array */
	aes_params.addrout = &aes_addrout[0];				/* output address array */

	aes_intin[0] = WindowHandle;
	aes_intin[1] = What;

	ptr = aes_control;
	*(ptr ++) = 104;									/* aes_control[0] */

	switch (What) {
		case WF_DCOLOR:
		case WF_COLOR:
			aes_intin[2] = *W1;
			*(ptr ++) = 3;								/* aes_control[1] */
			break;
		case WF_INFO:
		case WF_NAME:
			*(short**)&aes_intin[2] = W1;
			*(ptr ++) = 4;								/* aes_control[1] */
			break;
		default:
			*(ptr ++) = 2;								/* aes_control[1] */
	}

	*(ptr ++) = 5;										/* aes_control[2] */
	*(ptr ++) = 0;										/* aes_control[3] */
	*(ptr ++) = 0;				 						/* aes_control[4] */

	/* ol: this line is required for WF_FIRSTXYWH and WF_NEXTXYWH because
	   lot of programmers doesn't verify the return value and espect W or H
	   will be 0 it's not true for NAES */
	aes_intout[3] = aes_intout[4] = 0;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (W1)	*W1 = aes_intout[1];
	if (W2)	*W2 = aes_intout[2];
	if (W3)	*W3 = aes_intout[3];
	if (W4)	*W4 = aes_intout[4];
#else
	ptr = &aes_intout[1];
	*W1 = *(ptr ++);									/* aes_intout[1] */
	*W2 = *(ptr ++);									/* aes_intout[2] */
	*W3 = *(ptr ++);									/* aes_intout[3] */
	*W4 = *(ptr);										/* aes_intout[4] */
#endif

	return (aes_intout[0]);
}
