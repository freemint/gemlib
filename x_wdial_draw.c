#include "gem_aesP.h"
#include "mt_gemx.h"

/** Redraw a dialog within a window.
 *
 *  @param handle
 *  @param start
 *  @param depth
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured or non-zero otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_wdial_draw(short handle, short start, short depth, short *global_aes)
{
	AES_PARAMS(0x7150,3,1,0,0);

	aes_intin[0] = handle;
	aes_intin[1] = start;
	aes_intin[2] = depth;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
