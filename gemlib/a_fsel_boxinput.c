/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays the extended file selector and allows
 *  the user to select a valid GEMDOS path and file.
 *
 *  @param path see mt_fsel_exinput()
 *  @param file  see mt_fsel_exinput()
 *  @param exit_button  see mt_fsel_exinput()\n
 *         [option CHECK_NULLPTR] \a exit_button may be NULL
 *  @param label  see mt_fsel_exinput()
 *  @param callback is a pointer to a callback function. This callback function will
 *         be called by BoxKite when it received an AES message for the main application.
 *         It does not only concern the Message #WM_REDRAW and #WM_MOVED.
 *         Other messages are ignored. 
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured and 1 otherwise.
 *
 *  @since this extended call is available if BoxKite is installed (since version 1.71).
 *         The Cookie HBFS can be checked to test the availability
 *         of this function.
 *
 *  @sa mt_fsel_input() mt_fsel_exinput()
 *
 */

short
mt_fsel_boxinput (char *path, char *file, short *exit_button, const char *label, void * callback, short *global_aes)
{
	AES_PARAMS(91,0,2,4,0);

	aes_addrin[0] = (long)path;
	aes_addrin[1] = (long)file;
	aes_addrin[2] = (long)label;
	aes_addrin[1] = (long)callback;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (exit_button)
#endif
	*exit_button = aes_intout[1];

	return aes_intout[0];
}
