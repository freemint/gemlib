/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is designed to facilitate inter-process
 *  communication between processes running under the AES. The
 *  call will halt the application until a message of
 *  sufficient length is available (see version notes below).
 *
 *  @param ApId is your application identifier as returned by
 *         mt_appl_init().
 *  @param Length is the length (in bytes) of the message to read.
 *  @param ApPbuff is a pointer to a memory buffer where the incoming
 *         message should be copied to.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_write()
 *
 *  If the AES version is 4.0 or higher and appl_getinfo()
 *  indicates that this feature is supported, ap_id takes on an
 *  additional meaning. If APR_NOWAIT (-1) is passed instead of
 *  ap_id, appl_read() will return immediately if no message is
 *  currently waiting. 
 *
 *  Normally this call is not used. evnt_multi() or
 *  evnt_mesag() is used instead for standard message
 *  reception. appl_read() is required for reading messages
 *  that are long and/or of variable length.
 *  It is recommended that message lengths in multiples of 16
 *  bytes be used.
 */

short 
mt_appl_read(short ApId, short Length, void *ApPbuff, short *global_aes)
{
	AES_PARAMS({11,2,1,1,0});
                    
	aes_intin[0]  = ApId;
	aes_intin[1]  = Length;
	aes_addrin[0] = (long)ApPbuff;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_read
#undef appl_read
#endif
short 
appl_read(short ApId, short Length, void *ApPbuff)
{
	return(mt_appl_read(ApId, Length, ApPbuff, aes_global));
}

