/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Close file selector window or file selector dialog
 *
 *  @param fsd Descriptor that was passed at the 
 *		   successful opening of a file selector window.
 *  @param global_aes global AES array
 *
 *  @return 0 for error, else 1
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fslx_xx() functions availability
 *
 *  The corresponding descriptor is cleared and the file selector window or 
 *  dialog is closed.
 *
 *
 */

short 
mt_fslx_close(void *fsd, short *global_aes)
{
	AES_PARAMS(191,0,1,1,0);

	aes_addrin[0] = (long)fsd;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
