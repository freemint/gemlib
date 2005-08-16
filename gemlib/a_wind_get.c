/*
 *  $Id$
 */

#include "gem_aesP.h"

/** returns various information about a window.
 *
 *  @param WindowHandle specifies the handle of the window to return
 *         information about (0 is the desktop window)
 *  @param What specifies the information to return and the values
 *         placed into the WORDs pointed to by \a W1 to \a W4.
 *  @param W1 1st returned value \n
 *         [option CHECK_NULLPTR] \a W1 may be NULL
 *  @param W2 2nd returned value \n
 *         [option CHECK_NULLPTR] \a W2 may be NULL
 *  @param W3 3rd returned value \n
 *         [option CHECK_NULLPTR] \a W3 may be NULL
 *  @param W4 4th returned value \n
 *         [option CHECK_NULLPTR] \a W4 may be NULL
 *  @param global_aes global AES array
 *
 *  @return a 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions. \n
 *         #WF_KIND, #WF_NAME and #WF_INFO since NAES (release?).
 *
 *  @sa mt_wind_set()
 *
 *  <table><tr><td>Name<td>Value<td>  Meaning
 *  <tr><td> #WF_KIND <td> 1 <td>
 *           Gets the actual window elements
 * 	         - \a W1 contains the actual window elements
 *	                   with N.AES or MagiC.
 *
 *  <tr><td> #WF_NAME <td> 2 <td>
 * 	         Gets the actual title of the window
 *           - copies the title in the buffer pointed by \a W1.
 *
 *			 If the window has no title, the return
 *			 value of the function equals 0, the buffer
 *			 remains unchanged.
 *
 *			 Since a title may have a length of 128
 *			 chars, the buffer must be large enough!
 *
 *  <tr><td> #WF_INFO <td> 3 <td>
 * 	         Gets the actual infoline of the window
 *	         - copies the infoline in the buffer pointed by \a W1.
 *
 *			 If the window has no infoline, the return
 *			 value of the function equals 0, the buffer
 *			 remains unchanged.
 *
 *			 Since an infoline may have a length of 128
 *			 chars, the buffer must be large enough!
 *
 *   <tr><td> #WF_WORKXYWH <td> 4 <td>
 *            Gets the work area coordinates of the window
 *            - \a W1, \a W2, \a W3 and \a W4 are filled in with
 *               the x, y, w, and h of the current coordinates of
 *               the window's work area.
 *
 *  <tr><td> #WF_CURRXYWH <td> 5 <td>
 *           Gets the coordinates of the window (external area)
 *           - \a W1, \a W2, \a W3 and \a W4 are filled in with
 *             the x, y, w, and h of the current coordinates of
 *             the full extent of the window.
 *
 *  <tr><td> #WF_PREVXYWH <td> 6 <td>
 *           Gets the previous coordinates of the window
 *           - \a W1, \a W2, \a W3 and \a W4 are filled in with
 *             the x, y, w, and h of the previous coordinates of
 *             the full extent of the window prior to the last
 *             mt_wind_set() call.
 *
 *  <tr><td> #WF_FULLXYWH <td> 7 <td>
 *           Gets the coordinates of the window when "fulled" the screen
 *           - \a W1, \a W2, \a W3 and \a W4 are filled in with 
 *             the x, y, w, and h values specified in the mt_wind_create() call.
 *
 *  <tr><td> #WF_HSLIDE <td> 8 <td>
 *           Gets the current position of the horizontal slider
 *           - \a W1 is filled in with the current position of the
 *             horizontal slider between 0 and 1000. A value of one
 *             indicates that the slider is in its leftmost position.
 *
 *  <tr><td> #WF_VSLIDE <td> 9 <td>
 *           Gets the current position of the vertical slider
 *           - \a W1 is filled in with the current position of the 
 *             vertical slider between 0 and 1000. A value of one
 *             indicates that the slider is in its uppermost
 *             position.
 *
 *  <tr><td> #WF_TOP <td> 10 <td>
 *           Gets the handle of the top window
 *           - \a W1 is filled in with the window handle of the window
 *             currently on top.
 *           - \a W2 is filled in with the owners AES id
 *           - \a W3 is filled in with the handle of the window directly
 *             below it.
 *
 *           \a W2 and \a W3 are only filled by the AES since AES version 4.0,
 *           and when mt_appl_getinfo() with mode #AES_WINDOW indicates the
 *           availability of this feature.
 *
 *  <tr><td> #WF_FIRSTXYWH <td> 11 <td>
 *           Gets the first rectangle in the list of rectangles for this window
 *           - \a W1, \a W2, \a W3 and \a W4 are filled in with the
 *              x, y, w, and h of the first AES rectangle in the window's
 *              rectangle list.
 *
 *           If \a W3 and \a W4 are both 0, the window is completely covered.
 *
 *  <tr><td> #WF_NEXTXYWH <td> 12 <td>
 *           Gets the next rectangle in the list of rectangles for this window
 *           - \a W1, \a W2, \a W3 and \a W4 are filled in with subsequent
 *             AES rectangles for each time this function is called
 *             until \a W3 and \a W4 are 0 to signify the end of the list.
 *
 *  <tr><td> #WF_NEWDESK <td> 14 <td>
 *           Gets the OBJECT tree installed as desktop
 *           - \a W1 contains the high WORD of the address and \a W2
 *             contains the low WORD of the address of the current
 *             desktop background OBJECT tree.
 *
 *           Available as of AES versions 4.0, and when mt_appl_getinfo()
 *           with mode #AES_WINDOW indicates.
 *
 *  <tr><td> #WF_HSLSIZE <td> 15 <td>
 *           Gets the size of the horizontal slider
 *           - \a W1 contains the size of the current slider relative to
 *             the size of the scroll bar as a value from 0 to 1000.
 *             A value of 1000 indicates that the slider is at its maximum size.
 *
 *  <tr><td> #WF_VSLSIZE <td> 16 <td>
 *           Gets the size of the vertical slider
 *           - \a W1 contains the size of the current slider relative to 
 *             the size of the scroll bar as a value from 0 to 1000.
 *             A value of 1000 indicates that the slider is at its maximum size.
 *
 *  <tr><td> #WF_SCREEN <td> 17 <td>
 *           Gets current AES menu/alert buffer and its size
 *           - \a W1 contains the high WORD of the pointer to the AES buffer
 *           - \a W2 contains the low  WORD of the pointer to the AES buffer
 *           - The length of the buffer is returned as a LONG with
 *             the upper WORD being in \a W3 and the lower WORD being in \a W4.
 *
 *           Note that GEM 1.2 returns 0 in \a W3 and \a W4 by mistake.
 *
 *           The menu/alert buffer is used by the AES to save the screen area
 *           hidden by menus and alert boxes. It is not recommended that
 *           applications use this area as its usage is not guaranteed in
 *           future versions of the OS.
 *
 *  <tr><td> #WF_COLOR <td> 18 <td>
 *           Gets current color of widget
 *          - \a W1 point to a WORD that specify the index of the widget.
 *            Valid window widget indexes are as follows :
 *             - #W_BOX      (0)    ob_type : #G_IBOX
 *             - #W_TITLE    (1)    ob_type : #G_BOX								 		   
 *             - #W_CLOSER   (2)    ob_type : #G_BOXCHAR							 		   
 *             - #W_NAME	 (3)    ob_type : #G_BOXTEXT							 		   
 *             - #W_FULLER   (4)    ob_type : #G_BOXCHAR							 		   
 *             - #W_INFO	 (5)    ob_type : #G_BOXTEXT							 		   
 *             - #W_DATA	 (6)    ob_type : #G_IBOX 							 		   
 *             - #W_WORK	 (7)    ob_type : #G_IBOX 							 		   
 *             - #W_SIZER    (8)    ob_type : #G_BOXCHAR							 		   
 *             - #W_VBAR	 (9)    ob_type : #G_BOX								 		   
 *             - #W_UPARROW  (10)   ob_type : #G_BOXCHAR							 		   
 *             - #W_DNARROW  (11)   ob_type : #G_BOXCHAR							 		   
 *             - #W_VSLIDE   (12)   ob_type : #G_BOX								 		   
 *             - #W_VELEV    (13)   ob_type : #G_BOX								 		   
 *             - #W_HBAR	 (14)   ob_type : #G_BOX								 		   
 *             - #W_LFARROW  (15)   ob_type : #G_BOXCHAR							 		   
 *             - #W_RTARROW  (16)   ob_type : #G_BOXCHAR							 		   
 *             - #W_HSLIDE   (17)   ob_type : #G_BOX								 		   
 *             - #W_HELEV    (18)   ob_type : #G_BOX								 		   
 *             - #W_SMALLER  (19)   ob_type : #G_BOXCHAR (only valid as of AES 4.1)		   
 *          - \a W2 contains the ob_spec field of the object
 *            (containing the color information) while the window is on top.
 *          - \a W3 contains the ob_spec field of the object
 *            (containing the color information) while the window is not on top
 *
 *          This mode is only valid as of AES version 0x0300. From AES
 *          versions 4.0 and above, mt_appl_getinfo() with mode #AES_WINDOW
 *          should be used to determine if this mode is supported.
 *
 *
 *  <tr><td> #WF_DCOLOR <td> 19 <td>
 *          This mode gets the default color of newly created windows as with
 *          #WF_COLOR above.
 *
 *          This mode only works as of AES version 0x0300.
 *
 *
 *  <tr><td> #WF_OWNER <td> 20 <td>
 *           Gets the owner of the window
 *           - \a W1 is filled in with the AES id of the owner of the specified window.
 *           - \a W2 is filled in with its open status (0 = closed, 1 = open).
 *           - \a W3 is filled in with the handle of the window directly
 *             above it (in the window order list) 
 *           - \a W4 is filled in with the handle of the window below it (likewise, in the
 *              window order list)
 *
 *           This mode is only available as of AES version 4.0 (and when indicated by
 *           mt_appl_getinfo() with mode #AES_WINDOW).
 *
 *  <tr><td> #WF_BEVENT <td> 24 <td>
 *           Gets window feature on mouse button event
 *           - \a W1 is interpreted as bit arrays whose bits indicate supported
 *             window features. These bits are:
 *              - #BEVENT_WORK : window not topped when click on the work area
 *              - #BEVENT_INFO : ???
 *
 *           This mode is only available as of AES version 4.0 (and when indicated by
 *           mt_appl_getinfo() with mode #AES_WINDOW).
 *
 *  <tr><td> #WF_BOTTOM <td> 25 <td>
 *           Gets bottom window
 *           - \a W1 will be filled in with the handle of the window currently on
 *             the bottom of the window list (it may actually be on top if there
 *             is only one window). Note also that this does not include the
 *             desktop window.
 *
 *           This mode is only available as of AES version 4.0 (and when indicated by
 *           mt_appl_getinfo() with mode #AES_WINDOW).
 *
 *  <tr><td> #WF_ICONIFY <td> 26 <td>
 *           Gets iconification of the window
 *           - \a W1 will be filled in with 0 if the window is not iconified or
 *             non-zero if it is.
 *           - \a W2 and \a W3 contain the width and height of the icon.
 *           - \a W4 is unused.
 *
 *           This mode is only available as of AES version 4.1 (and when indicated by
 *           mt_appl_getinfo() with mode #AES_WINDOW).
 *
 *  <tr><td> #WF_UNICONIFY <td> 27 <td>
 *           Gets un-iconification of the window
 *           - \a W1, \a W2, \a W3 and \a W4, are filled in with the x, y, w, and h
 *             of the original coordinates of the iconified window.
 *
 *           This mode is only available as of AES version 4.1 (and when indicated by
 *           mt_appl_getinfo() with mode #AES_WINDOW).
 *
 *  <tr><td> #WF_TOOLBAR <td> 30 <td>
 *           Gets tool bar attached to a window
 *           - \a W1 and \a W2 contain the high and low WORD respectively of the pointer
 *             to the current toolbar object tree (or NULL if none).
 *
 *           This mode is only available as of AES version 4.1.
 *
 *  <tr><td> #WF_FTOOLBAR <td> 31 <td>
 *           Gets the first rectangle of the toolbar area
 *           - \a W1, \a W2, \a W3 and \a W4, are filled in with the x, y, w, and h,
 *             respectively of the first uncovered rectangle of the toolbar region
 *             of the window.
 *
 *           If \a W3 and \a W4 are 0, the toolbar is completely covered.
 *
 *           This mode is only available as of AES version 4.1.
 *
 *  <tr><td> #WF_NTOOLBAR <td> 32 <td>
 *           Gets the next rectangle of the toolbar area
 *           - \a W1, \a W2, \a W3 and \a W4, are filled in with the x, y, w, and h,
 *             respectively of subsequent uncovered rectangles of the toolbar region.
 *
 *           This mode should be repeated to reveal subsequent rectangles until \a W3
 *           and \a W4 are found to be 0.
 *
 *           This mode is only available as of AES version 4.1.
 *
 *  <tr><td> #WF_WIDGETS <td> 200 <td>
 *          Gets the actual positions of the slider widgets
 *          (#W_UPARROW, #W_DNARROW, and so on)
 *          - \a W1 and \a W2 are the vertical elements of type rightwidget (\a W1 is
 *            the top and \a W2 is the bottom widget of the vertical slider)
 *          - \a W3 and \a W4 are the horizontal elements of type bottomwidgets.
 *            (\a W3 is the left and \a W4 is the right widget of the horizotal
 *		      slider).
 *	</table>
 *
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
	aes_params.intin   = &aes_intin[0];				/* input integer array */
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
	
	if (What == WF_INFO || What == WF_NAME) {
		/* special case where W1 shall not be overwritten */
	} else {
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
	}

	return (aes_intout[0]);
}
