/*
 *  $Id$
 */

#include "gem_aesP.h"

/** manages the screen drawing semaphore.
 *
 *  @param Code specifies an action as follows:<pre>
Name       mode Meaning

END_UPDATE  0   This mode resets the flag set by BEG_UPDATE
                and should be called as soon as redrawing
                is complete. This will allow windows to be
                moved and menus to be dropped down again.

BEG_UPDATE  1   Calling this mode will suspend the process
                until no drop-down menus are showing and no
                other process is updating the screen. This
                will then set a flag which guarantees that
                the screen will not be updated and windows
                will not be moved until you reset it with
                END_UPDATE. Generally this call is made
                whenever a WM_REDRAW message is received to
                lock the screen semaphore while redrawing.

END_MCTRL   2   This mode releases control of the mouse to
                the AES and resumes mouse click message
                services.

BEG_MCTRL   3   This mode prevents mouse button messages
                from being sent to applications other than
                your own. mt_form_do() makes this call to lock
                out screen functions. Desk accessories
                which display a dialog outside of a window
                must use this function to prevent button
                clicks from falling through to the desktop.</pre>
 *  @param global_aes global AES array
 *
 *  @return  returns 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_wind_new()
 *
 *  As of AES version 4.0, you may logically OR a mask of
 *  NO_BLOCK (0x0100) to either BEG_UPDATE or BEG_MCTRL. This
 *  mask will prevent the application from blocking if another
 *  application currently has control of the screen semaphore.
 *  Instead, if another application has control, the function
 *  will immediately return with an error value of 0. This
 *  method should only be used by timing-sensitive applications
 *  such as terminal programs in which a long redraw by another
 *  application could cause a timeout.
 *
 *  All mt_wind_update() modes nest. For instance, to release the
 *  screen semaphore, the same number of END_UPDATE calls must
 *  be received as were BEG_UPDATE calls. It it recommended
 *  that you design your application in a manner that avoids
 *  nesting these calls. Both the BEG_UPDATE and BEG_MCTRL
 *  modes should be used prior to displaying a form or popup to
 *  prevent them from being overwritten or clicks to them being
 *  sent to other applications. Always wait until after the
 *  BEG_UPDATE call to turn off the mouse cursor when updating
 *  the screen to be sure you have gained control of the
 *  screen. Applications such as slide-show viewers which
 *  require the whole screen area (and may need to change
 *  screen modes) may call mt_wind_update() with parameters of
 *  both BEG_UPDATE and BEG_MCTRL to completely lock out the
 *  screen from other applications. The application would still
 *  be responsible for saving the screen area, manipulating
 *  video modes as necessary, restoring the screen when done,
 *  and returning control of the screen to other applications
 *  with END_UPDATE and END_MCTRL.
 */

short 
mt_wind_update (short Code, short *global_aes)
{
	AES_PARAMS(107,1,1,0,0);

	aes_intin[0] = Code;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}

#ifdef wind_update
#undef wind_update
#endif
short 
wind_update(short Code)
{
	return(mt_wind_update(Code, aes_global));
}
