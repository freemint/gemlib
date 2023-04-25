#include "gem_aesP.h"
#include "mt_gemx.h"

/** Extended file selector.
 *
 *  @param inpath
 *  @param pathlen
 *  @param insel
 *  @param sels
 *  @param exbutton
 *  @param label
 *  @param global_aes global AES array
 *
 *  @return 0 = An object was selected
 *
 *  @since Geneva
 *
 */

short
mt_x_fsel_input(char *inpath, short pathlen, char *insel, short sels,
     short *exbutton, const char *label, short *global_aes)
{
	AES_PARAMS(0x7120,2,2,3,0);

	aes_intin[0] = pathlen;
	aes_intin[1] = sels;
	aes_addrin[0] = (long)inpath;
	aes_addrin[1] = (long)insel;
	aes_addrin[2] = (long)label;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (exbutton)
#endif
	*exbutton = aes_intout[1];

	return aes_intout[0];
}
