/*
 *  $Id$
 */

#include "gem_aesP.h"

/** renders an AES object tree on screen.
 *
 *  @param tree  specifies the object tree to draw
 *  @param start specifies the object index at which drawing is to begin.
 *  @param depth specifies the maximum object depth to draw (a value
 *         of 1 searches only first generation objects, a value of 2
 *         searches up to second generation objects, up to a maximum
 *         of 7 to search all objects).
 *  @param cx x-position of the the clipping rectangle  
 *         to enforce during drawing.
 *  @param cy y-position of the the clipping rectangle
 *         to enforce during drawing.
 *  @param cw width of the the clipping rectangle
 *         to enforce during drawing.
 *  @param ch height of the the clipping rectangle
 *         to enforce during drawing.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred and non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_draw()
 *
 *  In general, if not redrawing the object, it is usually
 *  quicker to manipulate the object tree directly.
 *
 */

short 
mt_objc_draw(OBJECT *tree, short start, short depth,
             short cx, short cy, short cw, short ch, short *global_aes)
{
	AES_PARAMS(42,6,1,1,0);
                    
	aes_intin[0] = start;
	aes_intin[1] = depth;
	aes_intin[2] = cx;
	aes_intin[3] = cy;
	aes_intin[4] = cw;
	aes_intin[5] = ch;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
