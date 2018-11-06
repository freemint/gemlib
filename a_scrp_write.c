#include "gem_aesP.h"

/** sets the location of the clipboard directory.
 *
 *  @param Scrappath points to a NULL-terminated path string containing
 *         a valid drive and path specification with a closing
 *         backslash. The following is an example of a correctly
 *         formatted \a Scrappath argument: \c C:\\CLIPBRD\\
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_scrp_read()
 *
 *  The scrap directory is a global resource. This call should
 *  only be used in two circumstances as follows: when used to
 *  set the default location of the scrap directory using a CPX
 *  or accessory at bootup or by the user's request.
 *
 */

short 
mt_scrp_write(const char *Scrappath, short *global_aes)
{
	AES_PARAMS(81,0,1,1,0);
                    
	aes_addrin[0] = (long)Scrappath;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
