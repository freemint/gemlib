/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays the xxx file selector and allows
 *  the user to select a valid GEMDOS path and file.
 *
 *  @param path 
 *  @param file 
 *  @param exit_but All parameters are consistent with fsel_exinput() with the
 *                  notable lack of title. \n
 *             [option CHECK_NULLPTR] exit_but may be NULL
 *  @param label title for the fileselector
 *  @param callback (TODO: doc wanted!)
 *  @param global_aes global AES array
 *
 *  @return ?
 *
 *  @since the cookie HBFS give the availabity of this function.
 *
 *  @sa fsel_input fsel_exinput
 *
 */

short
mt_fsel_boxinput (char *path, char *file, short *exit_but, const char *label, void * callback, short *global_aes)
{
	AES_PARAMS(91,0,2,4,0);

	aes_addrin[0] = (long)path;
	aes_addrin[1] = (long)file;
	aes_addrin[2] = (long)label;
	aes_addrin[1] = (long)callback;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (exit_but)
#endif
	*exit_but = aes_intout[1];

	return aes_intout[0];
}
