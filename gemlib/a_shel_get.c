/*
 *  $Id$
 */

#include "gem_aesP.h"

/** copies the contents of the AES's shell buffer
 *  (normally the 'DESKTOP.INF' or 'NEWDESK.INF' file) into the
 *  specified buffer.
 *
 *  @param Buf points to a buffer at least...
 *  @param Len ...bytes long into which the AES should copy the shell
 *         buffer into.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_shel_put()
 *
 *  AES versions prior to version 1.4 had a shell buffer size
 *  of 1024 bytes. Versions 1.4 to 3.0 had a shell buffer size
 *  of 4192 bytes.
 *
 *  In AES versions 4.0 or greater the shell buffer is no
 *  longer of a fixed size. When appl_getinfo() indicates that
 *  this feature is supported, length can be specified as
 *  SHEL_BUFSIZE (-1) to return the size of the current shell
 *  buffer.
 *
 */

short 
mt_shel_get(char *Buf, short Len, short *global_aes)
{
	AES_PARAMS(122,1,1,1,0);
                    
	aes_intin[0]  = Len;
	aes_addrin[0] = (long)Buf;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef shel_get
#undef shel_get
#endif
short 
shel_get(char *Buf, short Len)
{
	return(mt_shel_get(Buf, Len, aes_global));
}

