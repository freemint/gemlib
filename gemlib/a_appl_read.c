/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is designed to facilitate inter-process
 *  communication between processes running under the AES. The
 *  call will halt the application until a message of
 *  sufficient length is available (see version notes below).
 *
 *  @param ap_id is your application identifier as returned by
 *         mt_appl_init().
 *  @param length is the length (in bytes) of the message to read.
 *  @param ap_pbuff is a pointer to a memory buffer where the incoming
 *         message should be copied to.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_write()
 *
 *  If the AES version is 4.0 or higher and mt_appl_getinfo()
 *  indicates that this feature is supported, ap_id takes on an
 *  additional meaning. If APR_NOWAIT (-1) is passed instead of
 *  ap_id, mt_appl_read() will return immediately if no message is
 *  currently waiting.
 *
 *  Normally this call is not used. mt_evnt_multi() or
 *  mt_evnt_mesag() is used instead for standard message
 *  reception. mt_appl_read() is required for reading messages
 *  that are long and/or of variable length.
 *  It is recommended that message lengths in multiples of 16
 *  bytes be used.
 */

short
mt_appl_read(short ap_id, short length, void *ap_pbuff, short *global_aes)
{
	AES_PARAMS(11,2,1,1,0);

	aes_intin[0]  = ap_id;
	aes_intin[1]  = length;
	aes_addrin[0] = (long)ap_pbuff;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_read
#undef appl_read
#endif
short
appl_read(short ap_id, short length, void *ap_pbuff)
{
	return(mt_appl_read(ap_id, length, ap_pbuff, aes_global));
}

