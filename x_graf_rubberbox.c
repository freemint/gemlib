#include "gem_aesP.h"
#include "mt_gemx.h"

/** Extended rubberband box drawing.
 *
 *  @param area
 *  @param outer
 *  @param minwidth
 *  @param minheight
 *  @param maxwidth
 *  @param maxheight
 *  @param snap
 *  @param lag
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured or non-zero otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_graf_rubberbox(GRECT *area, GRECT *outer, short minwidth,
     short minheight, short maxwidth, short maxheight, short snap, short lag, short *global_aes)
{
	AES_PARAMS(0x7131,6,1,2,0);

	aes_intin[0] = minwidth;
	aes_intin[1] = minheight;
	aes_intin[2] = maxwidth;
	aes_intin[3] = maxheight;
	aes_intin[4] = snap;
	aes_intin[5] = lag;
	aes_addrin[0] = (long)area;
	aes_addrin[1] = (long)outer;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
