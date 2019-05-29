#include "gem_aesP.h"

/** is used to modify an object's coordinates so
 *  that it will appear in the center of the display screen.
 *
 *  @param tree points to a valid #OBJECT structure which the
 *               application wishes to have centered.
 *  @param cx ,
 *  @param cy ,
 *  @param cw ,
 *  @param ch is a clipping rectangle suitable for
 *            use in objc_draw() returned. \n
 *             [option CHECK_NULLPTR] cx, cy, cw and/or ch may be NULL
 *
 *  @return is currently reserved. Currently it equals 1.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_draw()
 *
 *  The values that mt_form_center() returns in cx, cy, cw, and ch,
 *  are not necessarily the same as the object's. These values
 *  take into account negative borders, outlining, and
 *  shadowing. This is meant to provide a suitable clipping
 *  rectangle for mt_objc_draw()
 *
 */

short
mt_form_center(OBJECT *tree, short *cx, short *cy, short *cw, short *ch, short *global_aes)
{
	AES_PARAMS(54,0,5,1,0);

	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (cx)
#endif
	*cx = aes_intout[1];
#if CHECK_NULLPTR
	if (cy)
#endif
	*cy = aes_intout[2];
#if CHECK_NULLPTR
	if (cw)
#endif
	*cw = aes_intout[3];
#if CHECK_NULLPTR
	if (ch)
#endif
	*ch = aes_intout[4];

 	return aes_intout[0];
}
