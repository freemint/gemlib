/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays the system file selector and allows
 *  the user to select a valid GEMDOS path and file.
 *
 *  @param path 
 *  @param file 
 *  @param exit_but All parameters are consistent with fsel_exinput() with the
 *                  notable lack of title. \n
 *             [option CHECK_NULLPTR] exit_but may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or 1 otherwise.
 *
 *  @since All AES versions
 *
 *  @sa fsel_exinput
 *
 */

short
mt_fsel_input (char *path, char *file, short *exit_but, short *global_aes)
{
	AES_PARAMS(90,0,2,2,0);

	aes_addrin[0] = (long)path;
	aes_addrin[1] = (long)file;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (exit_but)
#endif
	*exit_but = aes_intout[1];

	return aes_intout[0];
}
