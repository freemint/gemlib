#include "gem_aesP.h"
#include "mt_gemx.h"

/** Get or alter a window's OBJECT tree and gadget control flags.
 *
 *  @param mode
 *  @param wt
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred or a value>0 otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_wind_tree(short mode, WIND_TREE *wt, short *global_aes)
{
	AES_PARAMS(0x7152,1,1,1,0);

	aes_intin[0] = mode;
	aes_addrin[0] = (long)wt;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
