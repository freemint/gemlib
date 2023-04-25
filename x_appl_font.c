#include "gem_aesP.h"
#include "mt_gemx.h"

/** Change the characteristics of the large font used by Geneva, and also the window gadget borders.
 *
 *  @param getset
 *  @param zero
 *  @param info
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_appl_font(short getset, short zero, XFONTINFO *info, short *global_aes)
{
	AES_PARAMS(0x7101,2,1,0,0);

	aes_intin[0] = getset;
	aes_intin[1] = zero;
	aes_addrin[0] = (long)info;

	AES_TRAP(aes_params);

	return (aes_intout[0]);
}
