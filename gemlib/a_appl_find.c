/*
 *  $Id$
 */

#include "gem_aesP.h"

/** searches the AES's current process list for a program named Name and,
 *  if present, returns the application identifier of the process.
 *
 *  @param Name is a pointer to a null-terminated ASCII string
 *         containing a valid GEMDOS filename (not including an
 *         extension) padded with blanks to be exactly 8 characters
 *         long (not including the NULL).
 *  @param global_aes global AES array
 *
 *  @return the application identifier of the process if it is found or
 *          -1 otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_appl_write(), mt_appl_init()
 *
 *  AES versions from 4.0 add several extensions to this call
 *  for the benefit of MultiTOS as follows: If the upper word
 *  of the CHAR * is 0xFFFF, the lower word is assumed to be
 *  the MiNT id and mt_appl_find() will return the AES application
 *  identifier.
 *  If the upper word of the CHAR * is 0xFFFE, the lower word
 *  is assumed to be the AES application identifier and the
 *  MiNT id is returned.
 *  If the upper word of the CHAR * is 0x0000, the current
 *  processes' application identifier is returned. This
 *  functionality only exists if the AES version is 4.0 and
 *  above and mt_appl_getinfo() indicates that it is available.
 */

short
mt_appl_find(const char *Name, short *global_aes)
{
	AES_PARAMS(13,0,1,1,0);

	aes_addrin[0] = (long)Name;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef appl_find
#undef appl_find
#endif
short
appl_find(const char *Name)
{
	return(mt_appl_find(Name, aes_global));
}


