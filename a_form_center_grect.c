#include "gem_aesP.h"

/** see mt_form_center()
 *
 *  @param tree mt_form_center()
 *  @param r mt_form_center()\n
 *             [option CHECK_NULLPTR] r may be NULL
 *  @param global_aes global AES array
 *
 *  @return  see mt_form_center()
 *
 *  @since  see mt_form_center()
 *
 */

short
mt_form_center_grect( OBJECT *tree, GRECT *r, short *global_aes)
{
	AES_PARAMS(54,0,5,1,0);

	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (r)
#endif
	*r = *(GRECT*)(aes_intout+1);

 	return aes_intout[0];
}
