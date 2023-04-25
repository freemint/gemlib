#include "gem_aesP.h"
#include "mt_gemx.h"

/** Center a dialog on the screen, taking into account all object attributes that can affect the outer border.
 *
 *  @param tree
 *  @param cx
 *  @param cy
 *  @param cw
 *  @param ch
 *  @param global_aes global AES array
 *
 *  @return 0 if an error has occurred
 *
 *  @since Geneva
 *
 */

short
mt_x_form_center(OBJECT *tree, short *cx, short *cy, short *cw, short *ch, short *global_aes)
{
	AES_PARAMS(0x7110,0,5,1,0);

	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*cx = aes_intout[0];
	*cy = aes_intout[1];
	*cw = aes_intout[2];
	*ch = aes_intout[3];

	return (aes_intout[0]);
}
