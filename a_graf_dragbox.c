#include "gem_aesP.h"

/** allows the user to move a box frame within
 *  the constraints of a bounding rectangle.
 *
 *  @param  w initial width of the box to draw.
 *  @param  h initial height of the box to draw.
 *  @param sx starting x screen coordinate
 *  @param sy starting y screen coordinate
 *  @param bx x-coordinate of the bounding rectangle.
 *  @param by y-coordinate of the bounding rectangle.
 *  @param bw width of the bounding rectangle.
 *  @param bh height of the bounding rectangle.
 *  @param rx will be filled in (on function exit) with the ending
 *            x position of the box. \n
 *             [option CHECK_NULLPTR] \a rx may be NULL
 *  @param ry will be filled in (on function exit) with the ending
 *            y position of the box. \n
 *             [option CHECK_NULLPTR] \a ry may be NULL
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred during
 *          execution or greater than zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_graf_slidebox()
 *
 *  This call should be made only when the mouse button is
 *  depressed. The call returns when the mouse button is
 *  released.
 *
 *  It is most often used to give the user a visual
 *  'clue' when an object is being moved on screen.
 *
 */

short
mt_graf_dragbox(short  w, short  h, short sx, short sy,
				short bx, short by, short bw, short bh, short *rx, short *ry, short *global_aes)
{
	AES_PARAMS(71,8,3,0,0);

	aes_intin[0] =  w;
	aes_intin[1] =  h;
	aes_intin[2] = sx;
	aes_intin[3] = sy;
	aes_intin[4] = bx;
	aes_intin[5] = by;
	aes_intin[6] = bw;
	aes_intin[7] = bh;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (rx)
#endif
	*rx = aes_intout[1];
#if CHECK_NULLPTR
	if (ry)
#endif
	*ry = aes_intout[2];

	return aes_intout[0];
}
