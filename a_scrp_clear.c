#include "gem_aesP.h"

/** clear the content of the clipboard directory
 *
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_scrp_read(), mt_scrp_write()
 *
 *  This function deletes all the files in the clipboard directory,
 *  (not only files named \c 'SCRAP.*').
 *
 */

short 
mt_scrp_clear( short *global_aes)
{
	AES_PARAMS(82,0,1,0,0);

	AES_TRAP(aes_params);

	return aes_intout[0];
}
