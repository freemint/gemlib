#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine further selected files
 *
 *  @param fsd Descriptor that was passed at a 
 *		   successful opening of a file selector
 *		   window
 *  @param fname see below
 *  @param global_aes global AES array
 *
 *  @return 0, when no further file is selected, \p fname is unchanged.\n
 *			1, when a filename after \p fname was copied.
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fslx_xx() functions availability
 *
 *
 *
 */

short 
mt_fslx_getnxtfile(void *fsd, char *fname, short *global_aes)
{
	AES_PARAMS(192,0,1,2,0);

	aes_addrin[0] = (long)fsd;
	aes_addrin[1] = (long)fname;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
