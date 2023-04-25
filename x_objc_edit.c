#include "gem_aesP.h"
#include "mt_gemx.h"

/** Process keyboard input into an editable field, with extensions.
 *
 *  @param tree
 *  @param edit_obj
 *  @param key_press
 *  @param shift_state
 *  @param edit_idx
 *  @param mode
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occured or non-zero otherwise.
 *
 *  @since Geneva
 *
 */

short
mt_x_objc_edit(OBJECT *tree, short edit_obj, short key_press,
     short shift_state, short *edit_idx, short mode, short *global_aes)
{
	AES_PARAMS(0x7140,5,2,1,0);

	aes_intin[0] = edit_obj;
	aes_intin[1] = key_press;
#if CHECK_NULLPTR
	if (edit_idx == 0) aes_intin[2] = -1; else
#endif
	aes_intin[2] = *edit_idx;
	aes_intin[3] = shift_state;
	aes_intin[4] = mode;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (edit_idx)
#endif
	*edit_idx = aes_intout[1];

	return aes_intout[0];
}
