/*
 *  $Id$
 */

#include "gem_aesP.h"

/** can be used to send a message to a valid message pipe.
 *
 *  @param ap_id is the application identifier of the process to which
 *         you wish to send the message.
 *  @param length specifies the number of bytes present in the message.
 *  @param ap_pbuff is a pointer to a memory buffer with at least
 *         \a length bytes available
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or greater than 0 if the message was
 *          sent successfully.
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_read(), mt_shel_write()
 *
 *  As of AES version 1.40, desk accessories may send
 *  #MN_SELECTED messages to the desktop to trigger desktop
 *  functions.
 *
 *  As of AES version 4.00 you can use mt_shel_write(7,...) to
 *  'broadcast' a message to all processes running with the
 *  exception of the AES itself, the desktop, and your own
 *  application. See mt_shel_write() for details.
 *
 *  It is recommended that you always send messages in 16 byte
 *  blocks using a WORD array of 8 elements as the AES does.
 *
 */

short
mt_appl_write(short ap_id, short length, void *ap_pbuff, short *global_aes)
{
	AES_PARAMS(12,2,1,1,0);

	aes_intin[0]  = ap_id;
	aes_intin[1]  = length;
	aes_addrin[0] = (long)ap_pbuff;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
