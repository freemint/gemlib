#include "gem_aesP.h"
#include "mt_gemx.h"

/** Handle mouse clicks in a dialog, including editable cursor movement.
 *
 *  @param tree
 *  @param mouse_x
 *  @param mouse_y
 *  @param clicks
 *  @param edit_obj
 *  @param next_obj
 *  @param edit_idx
 *  @param global_aes global AES array
 *
 *  @return 0 = An object was selected
 *
 *  @since Geneva
 *
 */

short
mt_x_form_mouse(OBJECT *tree, short mouse_x, short mouse_y, short clicks,
     short *edit_obj, short *next_obj, short *edit_idx, short *global_aes)
{
	AES_PARAMS(0x7113,6,4,1,0);

	aes_intin[0] = mouse_x;
	aes_intin[1] = mouse_y;
	aes_intin[2] = clicks;
#if CHECK_NULLPTR
	if (edit_obj == 0) aes_intin[3] = 0; else
#endif
	aes_intin[3] = *edit_obj;
#if CHECK_NULLPTR
	if (next_obj == 0) aes_intin[4] = 0; else
#endif
	aes_intin[4] = *next_obj;
#if CHECK_NULLPTR
	if (edit_idx == 0) aes_intin[5] = -1; else
#endif
	aes_intin[5] = *edit_idx;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (edit_obj)
#endif
	*edit_obj = aes_intout[1];

#if CHECK_NULLPTR
	if (next_obj)
#endif
	*next_obj = aes_intout[2];

#if CHECK_NULLPTR
	if (edit_idx)
#endif
	*edit_idx = aes_intout[3];

	return aes_intout[0];
}
