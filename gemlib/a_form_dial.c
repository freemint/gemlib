/*
 *  $Id$
 */

#include "gem_aesP.h"

/** is used to reserve and release screen space for
 *  dialog usage. In addition, it also optionally provides
 *  grow/shrink box effects.
 *
 *  @param mode specifies the action to take and the meaning of
 *               remaining parameters as follows:<pre>
               FMD_START   0   This mode reserves the screen space for
                               a dialog. x2, y2, w2, and h2, contain the
                               coordinates of the dialog to be used
                               (usually obtained through form_center()).

               FMD_GROW    1   This mode draws an expanding box from the
                               coordinates specified in x1, y1, w1, and h1
                               to the coordinates specified in x2, y2, w2,
                               and h2. This call is optional and is not
                               required to display a dialog.

               FMD_SHRINK  2   This mode draws a shrinking box from the
                               coordinates specified in x2, y2, w2, and h2
                               to the coordinates specified in x1, y1, w1,
                               and h1. This call is optional and is not
                               required to display a dialog.

               FMD_FINISH  3   This mode releases the screen space for
                               a dialog (previously reserved with mode 0).
                               x2, y2, w2, and h2 contain the coordinates
                               of the space to release. One of the
                               side-effects of this call is a WM_REDRAW
                               message sent to any window which the dialog
                               was covering.</pre>
 *  @param x1
 *  @param y1
 *  @param w1
 *  @param h1 the first rectangle (usage depends on \p mode)
 *  @param x2
 *  @param y2
 *  @param w2
 *  @param h2 the second rectangle (usage depends on \p mode)
 *  @param global_aes global AES array
 *
 *  @return non-zero if succeeded.
 *
 *  @since All AES versions.
 *
 *  @sa mt_graf_growbox(), mt_graf_shrinkbox()
 *
 *  The AES does not currently make use of mode FMD_START.
 *  The call should, however, still be executed for upward
 *  compatibility.
 *
 */

short
mt_form_dial(short mode,
			 short x1, short y1, short w1, short h1,
			 short x2, short y2, short w2, short h2, short *global_aes)
{
	AES_PARAMS(51,9,1,0,0);

	aes_intin[0] = mode;
	aes_intin[1] = x1;
	aes_intin[2] = y1;
	aes_intin[3] = w1;
	aes_intin[4] = h1;
	aes_intin[5] = x2;
	aes_intin[6] = y2;
	aes_intin[7] = w2;
	aes_intin[8] = h2;

	AES_TRAP(aes_params);

	return aes_intout[0];
}

#ifdef form_dial
#undef form_dial
#endif
short
form_dial(short mode,
		  short x1, short y1, short w1, short h1,
		  short x2, short y2, short w2, short h2)
{
	return(mt_form_dial( mode, x1, y1, w1, h1, x2, y2, w2, h2, aes_global));
}
