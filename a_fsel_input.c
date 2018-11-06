#include "gem_aesP.h"

/** displays the system file selector and allows
 *  the user to select a valid GEMDOS path and file.
 *
 *  @param path see mt_fsel_exinput()
 *  @param file see mt_fsel_exinput()
 *  @param exit_button see mt_fsel_exinput() \n
 *             [option CHECK_NULLPTR] exit_button may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or 1 otherwise.
 *
 *  @since All AES versions
 *
 *  @sa mt_fsel_exinput()
 *
 */

short
mt_fsel_input (char *path, char *file, short *exit_button, short *global_aes)
{
	AES_PARAMS(90,0,2,2,0);

	aes_addrin[0] = (long)path;
	aes_addrin[1] = (long)file;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (exit_button)
#endif
	*exit_button = aes_intout[1];

	return aes_intout[0];
}
