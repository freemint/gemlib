/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays the system file selector and offers
 *  the user an opportunity to choose a complete GEMDOS path
 *  specification.
 *
 *  @param path should be a pointer to a character buffer at least 260
 *		   bytes long. On input the buffer should
 *		   contain a complete GEMDOS path specification including
 *		   a drive specifier, path string, and wildcard mask as
 *		   follows: 'drive:\\path\\mask'. The mask can be any valid
 *		   GEMDOS wildcard (usually *.*).\n
 *         On function exit, \p path contains final path of the selected
 *         file (you will have to strip the mask)
 *  @param file should point to a character buffer 13 bytes long (12
 *         character filename plus NULL), or 260 bytes long if the application
 *         runs in MiNT domain (see Pdomain GEMDOS call). On input its contents will
 *         be placed on the filename line of the selector (usually
 *         this value can simply be a empty string). On function exit,
 *         file contains the filename which the user selected.
 *  @param exit_button is a short pointer which upon function exit will
 *         contain #FSEL_CANCEL (0) if the user selected CANCEL or
 *         #FSEL_OK (1) if OK. \n
 *         [option CHECK_NULLPTR] exit_button may be NULL
 *  @param title should be a pointer to a character string up to 30
 *         characters long which contains the title to appear in the
 *         file selector (usually indicates which action the user is
 *         about to take).
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured and 1 otherwise.
 *
 *  @since Available from AES version 1.40. If an older AES version is detected,
 *         this function will redirect the call to mt_fsel_input().
 *
 *  The path parameter to this function should be validated to
 *  ensure that the path actually exists prior to calling this
 *  function to prevent confusing the user.
 *
 *  This call should always be used as opposed to mt_fsel_input()
 *  when it is available (ie always with this lib). Otherwise, the user has no reminder
 *  as to what function s/he is actually undertaking.
 */

short
mt_fsel_exinput (char *path, char *file, short *exit_button, const char *title, short *global_aes)
{
	if ( ((global_aes[0] >= 0x140) &&  (global_aes[0] < 0x200)) || (global_aes[0]>=0x300) )
	{
		long *ptr_l;
		
		AES_PARAMS(91,0,2,3,0);

		ptr_l = aes_addrin;
		*(ptr_l ++) = (long)path;			/* aes_addrin[0] */
		*(ptr_l ++) = (long)file;			/* aes_addrin[1] */
		*(ptr_l)    = (long)title;			/* aes_addrin[2] */

		AES_TRAP(aes_params);
	
#if CHECK_NULLPTR
		if (exit_button)
#endif
		*exit_button = aes_intout[1];

		return  aes_intout[0];
	}
	else return(mt_fsel_input (path, file, exit_button, global_aes));
}
