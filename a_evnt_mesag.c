/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases control to the operating system until a valid
 *  system message is available in the applications' message pipe.
 *
 *  @param msg A pointer to an array of 8 WORD's to be used as
 *             a message buffer. This array contains:
 *             - msg[0] is the message type.
 *             - msg[1] is the AES application identifier of the
 *               sender
 *             - msg[2] contains the length of the message beyond 16
 *               bytes (use mt_appl_read() to read the excess)
 *               Currently all system messages return 0 in this
 *               slot. Only user-defined messages utilize a higher
 *               value
 *             - other fields depend on the type of message.
 *  @param global_aes global AES array
 *
 *  @return Currently reserved by Atari and currently is defined
 *          as a value of 1.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  Here is a list of system messages. You may refer to their documentation for more details
 *  about the content of the \a msg[] buffer.
 *               - #MN_SELECTED
 *               - #WM_REDRAW
 *               - #WM_TOPPED
 *               - #WM_FULLED
 *               - #WM_ARROWED
 *               - #WM_HSLID
 *               - #WM_VSLID
 *               - #WM_SIZED
 *               - #WM_MOVED
 *               - #WM_NEWTOP
 *               - #WM_UNTOPPED
 *               - #WM_ONTOP
 *               - #WM_BOTTOM
 *               - #WM_ICONIFY
 *               - #WM_UNICONIFY
 *               - #WM_ALLICONIFY
 *               - #WM_TOOLBAR
 *               - #AC_OPEN
 *               - #AC_CLOSE
 *               - #AP_TERM
 *               - #AP_TFAIL
 *               - #SHUT_COMPLETED
 *               - #RESCH_COMPLETED
 *               - #AP_DRAGDROP
 *               - #SH_WDRAW
 *               - #CH_EXIT
 *
 */

short mt_evnt_mesag (short msg[], short *global_aes)
{
	AES_PARAMS(23,0,1,1,0);

	aes_addrin[0] = (long)msg;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
