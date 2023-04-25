#include "gem_aesP.h"
#include "mt_gemx.h"

/** Convert to/from a standard GEMDOS filename in editable field in a dialog.
 *
 *  @param fmt
 *  @param obj
 *  @param to_from
 *  @param string
 *  @param global_aes global AES array
 *
 *  @return always 1
 *
 *  @since Geneva
 *
 */

short
mt_x_form_filename(OBJECT *tree, short obj, short to_from, char *string, short *global_aes)
{
	AES_PARAMS(0x7112,2,1,2,0);

	aes_intin[0] = obj;
	aes_intin[1] = to_from;
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)string;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
