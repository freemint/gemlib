/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases control to the operating system until a valid
 *  system message is available in the applications' message pipe.
 *
 *  @param msg A pointer to an array of 8 WORD's to be used as
 *             a message buffer. The array is filed in with the
 *             following values:
 *
\verbatim
               Index   Description               Possible Values    #

               msg[0]  Message Type              MN_SELECTED        10
                                                 WM_REDRAW          20
                                                 WM_TOPPED          21
                                                 WM_CLOSED          22
                                                 WM_FULLED          23
                                                 WM_ARROWED         24
                                                 WM_HSLID           25
                                                 WM_VSLID           26
                                                 WM_SIZED           27
                                                 WM_MOVED           28
                                                 WM_NEWTOP          29
                                                 WM_UNTOPPED        30
                                                 WM_ONTOP           31
                                                 WM_BOTTOMED        33
                                                 WM_ICONIFY         34
                                                 WM_UNICONIFY       35
                                                 WM_ALLICONIFY      36
                                                 WM_TOOLBAR         37
                                                 AC_OPEN            40
                                                 AC_CLOSE           41
                                                 AP_TERM            50
                                                 AP_TFAIL           51
                                                 AP_RESCHG          57
                                                 SHUT_COMPLETED     60
                                                 RESCH_COMPLETED    61
                                                 AP_DRAGDROP        63
                                                 SH_WDRAW           72
                                                 CH_EXIT            90

               msg[1]  The application           Any valid ap_id.
                       identifier of the
                       sending application.

               msg[2]  The length of the         Currently all system
                       message beyond 16 bytes   messages return 0 in this
                       (use appl_read() to read  slot. Only user-defined
                       the excess).              messages utilize a higher
                                                 value.

               Each system message can be interpreted as follows:

            Message           #  Extended Information


            MN_SELECTED      10  A menu item has been selected by the user.
                                 msg[3] contains the object number of the
                                 menu title and msg[4] contains the object
                                 number of the menu item.
                                 As of AES version 3.30 (and when indicated
                                 by appl_getinfo() ), msg[5] and msg[6]
                                 contain the high and low word,
                                 respectively, of the object tree of the
                                 menu item. msg[7] contains the parent
                                 object index of the menu item.


            WM_REDRAW        20  This message alerts an application that
                                 a portion of the screen needs to be
                                 redrawn. msg[3] contains the handle of the
                                 window to redraw. msg[4-7] are the x, y, w,
                                 and h respectively of the 'dirtied' area.
                                 When the message is received the window
                                 contents should be drawn (or a
                                 representative icon if the window is iconified).


            WM_TOPPED        21  This message is sent when an application
                                 window which is currently not the top
                                 window is clicked on by the user. msg[3]
                                 contains the handle of the window.
                                 You should use wind_set( msg[3], WF_TOP,
                                 0, 0, 0, 0) to actually cause the window to
                                 be topped.


            WM_CLOSED        22  This message is sent when the user clicks
                                 on a windows' close box. msg[3] contains
                                 the handle of the window to close.
                                 You should react to this message with
                                 wind_close().

            WM_FULLED        23  This message is sent when the user clicks
                                 on a windows' full box. If the window is
                                 not at full size, the window should be
                                 resized using wind_set(handle,
                                 WF_CURRXYWH,... to occupy the entire screen
                                 minus the menu bar (see wind_get()).
                                 If the window was previously 'fulled' and
                                 has not been resized since, the application
                                 should return the window to its previous
                                 size.

            WM_ARROWED       24  This message is sent to inform an
                                 application that one of its slider gadgets
                                 has been clicked on.
                                 A row or column message is sent when
                                 a slider arrow is selected. A 'page'
                                 message is sent when a darkened area of the
                                 scroll bar is clicked. This usually
                                 indicates that the application should
                                 adjust the window's contents by a larger
                                 amount than with the row or column
                                 messages.
                                 These messages are sent with the window
                                 handle in msg[3] and the operation code
                                 (as described) in msg[4]:

                                 Name      Value Meaning
                                 WA_UPPAGE   0   Page Up
                                 WA_DNPAGE   1   Page Down
                                 WA_UPLINE   2   Row Up
                                 WA_DNLINE   3   Row Down
                                 WA_LFPAGE   4   Page Left
                                 WA_RTPAGE   5   Page Right
                                 WA_LFLINE   6   Column Left
                                 WA_RTLINE   7   Column Right

            WM_HSLID         25  This message indicates that the horizontal
                                 slider has been moved. msg[4] contains the
                                 new slider position ranging from 0 to
                                 1000. msg[3] contain window handle.
                                 Note: Slider position is relative and not
                                       related to slider size.

            WM_VSLID         26  This message indicates that the vertical
                                 slider has been moved. msg[4] contains the
                                 new slider position ranging from 0 to
                                 1000. msg[3] contain window handle.
                                 Note: Slider position is relative and not
                                       related to slider size.

            WM_SIZED         27  This message occurs when the user drags the
                                 window sizing gadget. msg[3] contains the
                                 window handle. msg[4-7] indicate the x, y,
                                 w, and h respectively of the new window
                                 location.
                                 Use wind_set(handle, WF_CURRXYWH,... to
                                 actually size the window.
                                 WM_SIZED and WM_MOVED usually share common
                                 handling code.

            WM_MOVED         28  This message occurs when the user moves the
                                 window by dragging the windows' title bar.
                                 msg[3] contains the handle of the window
                                 being moved. msg[4-7] indicate the x, y, w,
                                 and h respectively of the new window
                                 location.
                                 Use wind_set(handle, WF_CURRXYWH,... ) to
                                 actually move the window.
                                 WM_MOVED and WM_SIZED usually share common
                                 handling code.

            WM_NEWTOP        29  This message occurs when the user topps
                                 the window.

            WM_UNTOPPED      30  This message is sent when the current
                                 window is sent behind one or more windows
                                 as the result of another window being
                                 topped. msg[3] contains the handle of the
                                 window being untopped.
                                 The application need take no action. The
                                 message is for informational use only.

            WM_ONTOP         31  This message is sent when an applications'
                                 window is brought to the front on
                                 a multitasking AES. msg[3] is the handle of
                                 the window being brought to the front.
                                 This message requires no action, it is for
                                 informational purposes only.

            WM_BOTTOMED      33  This message is sent when the user
                                 shift-clicks on the window's (specified in
                                 msg[3]) mover bar to indicate that the
                                 window should be sent to the bottom of the
                                 window stack by using wind_set() with
                                 a parameter of WF_BOTTOM.

            WM_ICONIFY       34  This message is sent when the user clicks
                                 on the SMALLER window gadget. msg[3]
                                 indicates the handle of the window to be
                                 iconified. msg[4-7] indicate the x, y, w,
                                 and h of the iconified window.
                                 If the iconified window represents
                                 a single window this message should be
                                 responded to by using wind_set() with
                                 a parameter of  WF_ICONIFY.

            WM_UNICONIFY     35  This message is sent when the user
                                 double-clicks on an iconified window.
                                 msg[3] indicates the handle of the window
                                 to be iconified. msg[4-7] indicate the x,
                                 y, w, and h of the original window.
                                 This message should be responded to by
                                 using wind_set() with a parameter of
                                 WF_UNICONIFY.

            WM_ALLICONIFY    36  This message is sent when the user
                                 ctrl-clicks on the SMALLER window gadget.
                                 msg[3] indicates which window's gadget was
                                 clicked. msg[4-7] indicates the position at
                                 which the new iconified window should be
                                 placed.
                                 The application should respond to this
                                 message by closing all open windows and
                                 opening a new iconified window at the
                                 position indicated which represents the
                                 application.

            WM_TOOLBAR       37  This message is sent when a toolbar object
                                 is clicked. msg[3] contains the handle of
                                 the window containing the toolbar.
                                 msg[4] contains the object index of the
                                 object clicked. msg[5] contains the number
                                 of clicks. msg[6] contains the state of the
                                 keyboard shift keys at the time of the
                                 click (as in evnt_keybd() ).

            AC_OPEN          40  This message is sent when the user has
                                 selected a desk accessory to open. msg[4]
                                 contains the application identifier (as
                                 returned by appl_init()) of the accessory
                                 to open.

            AC_CLOSE         41  This message is sent to a desk accessory
                                 when the accessory should be closed. msg[3]
                                 is the application identifier (as returned
                                 by appl_init()) of the accessory to close.
                                 Do not close any windows your accessory
                                 had open, the system will do this for you.
                                 Also, do not require any feedback from the
                                 user when this is received. Treat this
                                 message as a 'Cancel' from the user.

            AP_TERM          50  This message is sent when the system
                                 requests that the application terminate.
                                 This is usually the result of a resolution
                                 change but may also occur if another
                                 application sends this message to gain
                                 total control of the system.
                                 The application should shut down
                                 immediately after closing windows, freeing
                                 resources, etc... msg[5] indicates the
                                 reason for the shut down as follows:
                                 AP_TERM   (50) = Just shut down.
                                 AP_RESCHG (57) = Resolution Change.
                                 If for some reason, your process can not
                                 shut down you must inform the AES by
                                 sending an AP_TFAIL (51) message by using
                                 shel_write() mode 10 (see shel_write()).
                                 Note: Desk Accessories wil always be sent
                                       AC_CLOSE messages, not AP_TERM.

            AP_TFAIL         51  This message should be sent to the system
                                 (see shel_write()) when an application has
                                 received an AP_TERM (50) message and cannot
                                 shut down.
                                 msg[0] should contain AP_TFAIL and msg[1]
                                 should contain the application error code.

            AP_RESCHG        57  This message is actually a sub-command and
                                 is only found as a possible value in the
                                 AP_TERM (50) message (see above).

            SHUT_COMPLETED   60  This message is sent to the application
                                 which requested a shutdown when the
                                 shutdown is complete and was successful.

            RESCH_COMPLETED  61  This message is sent to an application when
                                 a resolution change it requested is
                                 completed. msg[3] contains 1 if the
                                 resolution change was successful and 0 if
                                 an error occurred.

            AP_DRAGDROP      63  This message indicates that another
                                 application wishes to initiate a drap and
                                 drop session. msg[3] indicates the handle
                                 of the window which had an object dropped
                                 on it or -1 if no specific window was
                                 targeted.
                                 msg[4-5] contains the X and Y position of
                                 the mouse when the object was 'dropped'.
                                 msg[6] indicates the keyboard shift state
                                 at the time of the drop (as in evnt_keybd()).
                                 msg[7] is a two-byte ASCII packed pipe
                                 identifier which gives the file extension
                                 of the pipe to open.
                                 For more information see
                                                   The Drag & Drop Protocol

            SH_WDRAW         72  This message is sent to the Desktop to ask
                                 it to update an open drive window. msg[3]
                                 should contain the drive number to update
                                 (0 = A:, 1 = B:) or -1 to update all
                                 windows.

            CH_EXIT          90  This message is sent when a child process
                                 that the application has started, returns.
                                 msg[3] contains the child's application
                                 identifier and msg[4] contains its exit
                                 code.
\endverbatim
 *
 *  @return Currently reserved by Atari and currently is defined
 *          as a value of 1.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  WM_UNTOPPED, WM_ONTOP, AP_TERM, AP_TFAIL, AP_RESCHG,
 *  SHUT_COMPLETED,  RESCH_COMPLETED, and CH_EXIT are new as of
 *  AES version 4.0.
 *  WM_BOTTOMED, WM_ICONIFY, WM_UNICONIFY, WM_ALLICONIFY, and
 *  WM_TOOLBAR are new as of AES version 4.1.
 *  No lower version AES will send these messages.
 *  The existence (or acceptance) of these messages should also
 *  be checked for by using mt_appl_getinfo().
 *
 */

short mt_evnt_mesag (short msg[], short *global_aes)
{
	AES_PARAMS(23,0,1,1,0);

	aes_addrin[0] = (long)msg;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
