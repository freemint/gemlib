/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Event Messag
 *
 *  AES Opcode: 23 (0x17)
 *
 *  Releases control to the operating system until
 *  a valid system message is available in the applications'
 *  message pipe.
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
 *  @param msg A pointer to an array of 8 WORD's to be used as
 *             a message buffer.
 *
 *             FIXME: TODO There is a lot of doc about this in AC - What shall we do?
 *
 *  @return Currently reserved by Atari and currently is defined
 *          as 1 FIXME?. The array msg is filed in with the following values:
 *
 */


short mt_evnt_mesag (short MesagBuf[], short *global_aes)
{
	AES_PARAMS({23,0,1,1,0});

	aes_addrin[0] = (long)MesagBuf;

	AES_TRAP(aes_params);

	return aes_intout[0];
}


#ifdef evnt_mesag
#undef evnt_mesag
#endif
short evnt_mesag(short MesagBuf[])
{
	return(mt_evnt_mesag(MesagBuf, aes_global));
}
