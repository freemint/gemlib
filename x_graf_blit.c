#include "gem_aesP.h"
#include "mt_gemx.h"

/** Blit one area of the screen to another location, or save/restore a block of screen data.
 *
 *  @param source
 *  @param dest
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured or non-zero otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_graf_blit(GRECT *source, GRECT *dest, short *global_aes)
{
	AES_PARAMS(0x7130,0,1,2,0);

	aes_addrin[0] = (long)source;
	aes_addrin[1] = (long)dest;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
