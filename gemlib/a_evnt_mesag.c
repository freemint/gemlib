/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases control to the operating system until a valid
 *  system message is available in the applications' message pipe.
 *
 *  @param msg A pointer to an array of 8 WORD's to be used as
 *             a message buffer. This array contains:
 *             - msg[0] is the message type. Here is a list of system
 *               messages:
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
 *               - #
 *               - #
 *               - #
 *             - msg[1] is the AES application identifier of the
 *               sender
 *             - msg[2] contains tje length of the message beyond 16
 *               bytes (use mt_appl_read() to read the excess)
 *               Currently all system messages return 0 in this
 *               slot. Only user-defined messages utilize a higher
 *               value
 *             - other fields depend on the type of message. Refer
 *               to the table below for details.
 *  @param global_aes global AES array
 *
 *  @return Currently reserved by Atari and currently is defined
 *          as a value of 1.
 *
 *  @since All AES versions.
 *
 *  @sa mt_evnt_multi()
 *
 *  #WM_UNTOPPED, #WM_ONTOP, #AP_TERM, #AP_TFAIL, #AP_RESCHG,
 *  #SHUT_COMPLETED,  #RESCH_COMPLETED, and #CH_EXIT are new as of
 *  AES version 4.0.
 *  #WM_BOTTOMED, #WM_ICONIFY, #WM_UNICONIFY, #WM_ALLICONIFY, and
 *  #WM_TOOLBAR are new as of AES version 4.1.
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
