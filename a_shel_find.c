/*
 *  $Id$
 */

#include "gem_aesP.h"

/** searches for a file along the AES's current
 *  path, any paths specified by the 'PATH' environmental
 *  variable, and the calling application's path.
 *
 *  @param buf should point to a character buffer of at least 260
 *		   characters and contain the filename of the file to search
 *		   for on entry. If the function was able to find the file,
 *		   the buffer pointed to by buf will be filled in with the
 *		   full pathname of the file upon return.
 *  @param global_aes global AES array
 *
 *  @return 0 if the file was not found or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_shel_write()
 *
 */
 
short 
mt_shel_find(char *buf, short *global_aes)
{
	AES_PARAMS(124,0,1,1,0);

   	aes_addrin[0] = (long)buf;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
