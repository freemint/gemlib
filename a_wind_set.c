#include "gem_aesP.h"

/** sets various window attributes.
 *
 *  @param WindowHandle specifies the window handle of the window to modify.
 *  @param What specifies the attribute to change and the meanings of
 *         parameters \a W1 to \a W4
 *  @param W1 see hereafter
 *  @param W2 see hereafter
 *  @param W3 see hereafter
 *  @param W4 see hereafter
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  <table><tr><td>Name<td>Value<td>  Meaning
 *  <tr><td> #WF_NAME <td> 2 <td>
 *           This mode passes a pointer to a character string containing
 *           the new title of the window.
 *           - \a W1 contains the high WORD of the pointer
 *           - \a W2 contains the low WORD of the pointer
 *
 * <tr><td> #WF_INFO   <td>        3  <td>
 *          This mode passes a pointer to a character string containing
 *          the new information line of the window.
 *          - \a W1 contains the high WORD of the pointer
 *          - \a W2 contains the low WORD of the pointer
 *
 * <tr><td> #WF_CURRXYWH  <td>     5  <td>
 *          returns the global dimensions (external area) of the window)
 *          - \a W1, \a W2, \a W3 and \a W4 specify the x, y, w,
 *            and h of the new coordinates of the full extent
 *            of the window.
 *
 * <tr><td> #WF_HSLIDE  <td>       8  <td>
 *          Sets the position of the horizontal slider
 *          - \a W1 specifies the new position of
 *            the horizontal slider between 1 and 1000.
 *            A value of 1 indicates that the slider is in its
 *            leftmost position.
 *
 * <tr><td> #WF_VSLIDE  <td>       9 <td>
 *          Sets the position of the vertical slider
 *          - \a W1 specifies the new position of
 *            the vertical slider between 1 and 1000.
 *            A value of 1 indicates that the slider is in its
 *            uppermost position.
 *
 * <tr><td> #WF_TOP    <td>        10 <td>
 *          Tops a window
 *          - parameters \a W1 to \a W4 are unused . \a WindowHandle
 *            specifies the window handle of the window to top
 *
 *          Note that if multiple calls of mt_wind_set() with #WF_TOP,
 *          are made without releasing control to the AES (which allows the
 *          window to actually be topped), only the most recent window
 *          specified will actually change position.
 *
 * <tr><td> #WF_NEWDESK   <td>     14  <td>
 *          This mode allows to install or uninstall a desktop tree.
 *          This OBJECT tree whill be redrawn automatically by the
 *          AES as the background.
 *          - \a W1 contains the high WORD of the OBJECT pointer
 *          - \a W2 contains the low WORD of the OBJECT pointer.
 *
 *          To reset (uninstall) the desktop background to the default,
 *          specify \a W1 and \a W2 as 0 (that is OBJECT = NULL).
 *
 * <tr><td> #WF_HSLSIZE  <td>      15 <td>
 *          Sets the size of the horizontal slider
 *          - \a W1 defines the size of the current slider relative
 *            to the size of the scroll bar as a value from 1
 *            to 1000. A value of 1000 indicates that the slider is
 *            at its maximum size.
 *
 * <tr><td> #WF_VSLSIZE  <td>      16 <td>
 *          Sets the size of the vertical slider
 *          - \a W1 defines the size of the current slider relative
 *            to the size of the scroll bar as a value from 1
 *            to 1000. A value of 1000 indicates that the slider is
 *            at its maximum size.
 *
 * <tr><td> #WF_COLOR    <td>      18 <td>
 *          Sets the current color of window widgets
 *          - \a W1 specifies the index of the widget to modify.
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
 *          - \a W2 specifies the ob_spec field of the object
 *            (containing the color information) while the window is on top.
 *          - \a W3 specifies the ob_spec field of the object
 *            (containing the color information) while the window is not on top
 *
 *          This mode is only valid as of AES version 0x0300.
 *
 * <tr><td> #WF_DCOLOR  <td>       19 <td>
 *          This mode sets the default color of newly created windows as with
 *          #WF_COLOR above.
 *
 *          This mode only works as of AES version 0x0300.
 *
 *          As of AES version 4.1, this mode causes all currently displayed windows
 *          which have not had their color explicitly set with #WF_COLOR to be changed.
 *
 * <tr><td> #WF_BEVENT   <td>      24 <td>
 *          Sets/unsets window features on mouse button event
 *          - \a W1 is a bitmap fields. Its bits are defined as follow:
 *             - #BEVENT_WORK : the window is set to be 'un-toppable'
 *                and will never receive #WM_TOPPED message when the user
 *                clicks on the work area of the window.
 *                This mode is only available as of AES versions 4.0.
 *             - #BEVENT_INFO : MagiC 6 only... (meaning ????)
 *
 * <tr><td> #WF_BOTTOM  <td>       25  <td>
 *          This mode will place the specified window at the bottom of the window
 *          list (if there is more than one window) and top the new window on
 *          the top of the list. This mode is only available as of AES version 4.0.
 *
 * <tr><td> #WF_ICONIFY  <td>      26 <td>
 *          This mode iconifies the specified window.
 *          - \a W1, \a W2, \a W3 and \a W4 specify the X, Y, width, and
 *            height coordinates of the iconified window.
 *
 *          Normally, this happens as the result of receiving a #WM_ICONIFY message.
 *
 *          This mode is only available as of AES version 4.1.
 *
 * <tr><td> #WF_UNICONIFY  <td>    27 <td>
 *          This mode uniconifies the window specified
 *          - \a W1, \a W2, \a W3 and \a W4 specify  the X, Y, width, and
 *            height coordinates of the un-iconified window.
 *
 *          Normally, this happens as the result of receiving a #WM_UNICONIFY
 *          message.
 *
 *          This mode is only available as of AES version 4.1.
 *
 * <tr><td> #WF_UNICONIFYXYWH <td> 28  <td>
 *          This mode sets the coordinates to be transmitted to the
 *          window with the next #WM_UNICONIFY message that targets
 *          it. This call is used when a window is opened in an iconified state to
 *          give the OS a method of positioning it when it is uniconified.
 *          - \a W1, \a W2, \a W3 and \a W4 specify  the X, Y, width, and
 *            height coordinates of the un-iconified window.
 *
 *          This mode is only available as of AES version 4.1.
 *
 * <tr><td> #WF_TOOLBAR  <td>      30 <td>
 *          This mode attaches a toolbar to the specified window.
 *          - \a W1 and \a W2 contain the high and low WORD of the
 *            address of the toolbar OBJECT tree respectively.
 *          - \a W3 and \a W4 are unused.
 *
 *          Set \a W1 and \a W2 to 0 to remove a toolbar.
 *
 *          This mode is available as of AES 4.10.
 *
 *
 * <tr><td> #WF_WHEEL	<td>	40	<td>
 *          This mode allows to configure the feature of window on
 *          mouse wheel events
 *          - \a WindowHandle handle of the window, or -1 to apply the setting to all windows
 *            that will be created later by the application.
 *          - \a W1 may be one of the following value:
 *             -  #WHEEL_MESAG : AES will send #WM_WHEEL messages
 *             -  #WHEEL_ARROWED : AES will send #WM_ARROWED messages
 *             -  #WHEEL_SLIDER : AES will convert mouse wheel events to slider events
 *         
 *         Please note that it's not mandatory to explicitly set the #WO0_WHEEL bit of #WF_OPTS
 *         to enable this mouse wheel feature. A simple mt_wind_set(#WF_WHEEL) is enought.
 *         
 *         XaAES supports these 3 values of \a W1. MyAES (xmas 2005 edition) only support
 *         #WHEEL_MESAG value. So if you want your application to support the mouse wheel with
 *         both MyAES and XaAES, you should use #WHEEL_MESAG.
 *
 *         mt_appl_getinfo() with parameter #AES_WINDOW returns the availability of this mode.
 *					   					
 * <tr><td> #WF_OPTS	<td>	41	<td>
 *          This mode allows to configure the feature of window on
 *          mouse wheel events
 *          - \a WindowHandle may be 0 (=> all the windows of the calling
 *            application are then concerned)
 *          - \a W1 is the mode : 0 = clear, 1 = set option bits
 *          - \a W2 is the the first option word bitmask. Bits are defined as
 *            follow:
 *				- #WO0_WHEEL (0x0001) : Setting this bit will enable extended mouse
 *				  wheel support. Then, the reaction of applications on mouse wheel turns
 *				  may be tuned by calling mt_wind_set() with #WF_WHEEL command.
 *				- #WO0_FULLREDRAW (0x0002) : Setting this bit will make AES send
 *				  #WM_REDRAW messages to cover the whole work-area of the window when it is
 *				  FULLED. Default behaviour is to only send #WM_REDRAW messages for the areas
 *				  that need it, blitting the already visible parts.
 *				- #WO0_NOBLITW (0x0004) : Setting this bit will make AES send #WM_REDRAW
 *				  messages to cover the whole work-area of the window when its WIDTH changes.
 *				  This is handy for apps like HighWire, Textprocessors ,etc, that need to reformat
 *				  when window width changes. Default behaviour is to send #WM_REDRAW messages
 *				  for the areas that need it.
 *				- #WO0_NOBLITH (0x0008) : Setting this bit will make AES send #WM_REDRAW
 *				  messages to cover the whole work-area of the window when its HEIGHT changes.
 *				  Default behaviour is to send #WM_REDRAW messages for the areas that need it.
 *				- #WO0_SENDREPOS (0x0010) : Setting this bit will make AES send a
 *				  #WM_REPOSED message when a windows X/WIDTH and/or Y/HEIGHT coordinate pair changes.
 *				  Such changes happen when the user resizes the window using upper/left borders.
 *				  Default behaviour is to first send a #WM_MOVED followed by a #WM_SIZED
 *				  message under these conditions, because older apps dont evaluate the
 *          	  WIDTH/HEIGHT in WM_MOVED messages.
 *          - \a W3 is the 2nd option word bitmask. Should be set to #WO1_NONE (bits are not defined
 *                yet)
 *          - \a W4 is the 3rd option word bitmask. Should be set to #WO2_NONE (bits are not defined
 *                yet)
 *
 *         mt_appl_getinfo() with parameter #AES_WINDOW returns the availability of this mode.
 *         mt_appl_getinfo() with parameter #AES_WOPTS returns the support of WOx_xxx feature .
 *					   					
 * <tr><td> #WF_WIDGETS  <td>      200 <td>
 *          Sets the actual positions of the slider widgets
 *          (#W_UPARROW, #W_DNARROW, and so on)
 *          - \a W1 and \a W2 are the vertical elements of type rightwidget (\a W1 is
 *            the top and \a W2 is the bottom widget of the vertical slider)
 *          - \a W3 and \a W4 are the horizontal elements of type bottomwidgets.
 *            (\a W3 is the left and \a W4 is the right widget of the horizotal
 *		      slider).
 *
 * <tr><td> #WF_USER_POINTER  <td>      230 <td>
 *          Link a user value to the windows
 *          - \a W1 and \a W2 are the 2 value you can transmit it could be used as 32 bits pointer but any value can be provided
 *
 *          MyAES feature
 *
 * <tr><td> #WF_WIND_ATTACH   <td>      231 <td>
 *          attach a window to another, using it if you close the mother window other windows linked will be closed
 *          - \a W1 the window to attach
 *
 *          MyAES feature
 *					   					
 * <tr><td> #WF_TOPMOST  <td>      232 <td>
 *          Sets the actual window at topmost level (details below).
 *          - \a W1 should be set to one of the following values:
 *             - 0 : remove topmost state.
 *             - 1 : Set topmost state at global level
 *             - 2 : Set topmost state at application level
 *          - \a W2, \a W3 and \a W4 are reseved and should be set to 0.
 *
 *          Topmost windows always 'float' ontop of classical windows.
 *          One key feature of windows in any WF_TOPMOST state is that they do not
 *          disturb current keyboard focus, and can be used to issue important
 *          messages, status raports, etc., without demanding user interaction. As
 *          consequence, topmost window never get keyboard focus, and they never get
 *          WM_TOPPED or WM_UNTOPPED AES messages
 *
 *          Mode 1 of topmost windows fits well for task bar applications for example
 *          (window displayed whatever the active application)
 *
 *          Mode 2 of topmost windows fits well for toolbox windows: the visibility of
 *          the window is linked to the application that has the focus. That is, when owner
 *          is untopped the toolbox window disappears, when owner regains focus, the
 *          window automatically reappears (no action required by the application, opening and
 *          closing of the window is performed by the AES).
 *
 *          MyAES feature
 * 
 * <tr><td> #WF_OPTIONS  <td>      234 <td>
 *          Change window behavior
 *          - \a W1 only one value available for the moment:
 *            - 1 : request automatic close when application focus is lost and restore it when is back
 *                  to add this feature or remove it you should use \a W2 
 *          - \a W2  remove/add option:
 *            - 1 : add option
 *            - 0 : remove option
 *
 *          MyAES feature
 *
 * <tr><td> #WF_FULLSCREEN   <td>      235 <td>
 *          Switch fullscreen - normal window mode. The fullscreen mode is without any widget.
 *          Hit the key ESC escape from fullscreen mode  
 *
 *          MyAES 0.96 feature
 *
 *     
 *	</table>
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_get()
 *
 *  @note Under MyAES if \a WindowHandle is set to -2 then it is possible to know if option \a What is avaible or not,
 *  if available then return is 1 else return value is 0
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
