/*
 *  $Id$
 */

#include "gem_aesP.h"

/** copies information into the AES's shell buffer.
 *
 *  @param Buf points to a user memory buffer from which...
 *  @param Len ...bytes are to be copied into the shell buffer.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_shel_get()
 *
 *  Prior to AES version 4.0 this function would only copy as
 *  many bytes as would fit into the current buffer. As of
 *  version 4.0, the AES will dynamically allocate more memory
 *  as needed (up to 32767 bytes) for the shell buffer.
 *
 *  The Desktop uses the information in the shell buffer for
 *  several purposes. Applications should not use the shell
 *  buffer for their own purposes.
 */

short 
mt_shel_put(const char *Buf, short Len, short *global_aes)
{
	AES_PARAMS(123,1,1,1,0);

 	aes_intin[0]  = Len;
	aes_addrin[0] = (long)Buf;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
