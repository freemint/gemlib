#include "gem_aesP.h"

/** is used to reserve and release screen space for
 *  dialog usage. In addition, it also optionally provides
 *  grow/shrink box effects.
 *
 *  @param mode specifies the action to take and the meaning of
 *               remaining parameters as follows:
 *               - #FMD_START :  This mode reserves the screen space for
 *                               a dialog. \a x2, \a y2, \a w2, and \a h2, contain the
 *                               coordinates of the dialog to be used
 *                               (usually obtained through mt_form_center()).
 *               - #FMD_GROW     This mode draws an expanding box from the
 *                               coordinates specified in \a x1, \a y1, \a w1, and \a h1
 *                               to the coordinates specified in \a x2, \a y2, \a w2,
 *                               and \a h2. This call is optional and is not
 *                               required to display a dialog.
 *               - #FMD_SHRINK   This mode draws a shrinking box from the
 *                               coordinates specified in \a x2, \a y2, \a w2, and \a h2
 *                               to the coordinates specified in \a x1, \a y1, \a w1,
 *                               and \a h1. This call is optional and is not
 *                               required to display a dialog.
 *               - #FMD_FINISH   This mode releases the screen space for
 *                               a dialog (previously reserved with mode #FMD_START).
 *                               \a x2, \a y2, \a w2, and \a h2 contain the coordinates
 *                               of the space to release. One of the
 *                               side-effects of this call is a #WM_REDRAW
 *                               message sent to any window which the dialog
 *                               was covering.
 *  @param little the first rectangle (usage depends on \a mode)
 *  @param big the second rectangle (usage depends on \a mode)
 *  @param global_aes global AES array
 *
 *  @return non-zero if succeeded.
 *
 *  @since All AES versions.
 *
 *  @sa mt_graf_growbox(), mt_graf_shrinkbox()
 *
 *  The AES does not currently make use of mode #FMD_START.
 *  The call should, however, still be executed for upward
 *  compatibility.
 *
 */

short
mt_form_dial_grect(short mode, const GRECT *little, const GRECT *big, short *global_aes)
{
	AES_PARAMS(51,9,1,0,0);

	aes_intin[0] = mode;
	aes_intin[1] = little->g_x;
	aes_intin[2] = little->g_y;
	aes_intin[3] = little->g_w;
	aes_intin[4] = little->g_h;
	aes_intin[5] = big->g_x;
	aes_intin[6] = big->g_y;
	aes_intin[7] = big->g_w;
	aes_intin[8] = big->g_h;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
