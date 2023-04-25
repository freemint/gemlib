#include "gem_aesP.h"
#include "mt_gemx.h"

/** Redraw one object within a window dialog, showing a new state.
 *
 *  @param handle
 *  @param statr
 *  @param newstate
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured or non-zero otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_wdial_draw(short handle, short start, short newstate, short *global_aes)
{
	AES_PARAMS(0x7150,3,1,0,0);

	aes_intin[0] = handle;
	aes_intin[1] = start;
	aes_intin[2] = newstate;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
