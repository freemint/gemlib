#include "gem_aesP.h"

/** adds/removes a checkmark in front of a menu item.
 *
 *  @param me_tree specifies the object tree of the current menu
 *  @param me_item should be the object index of a menu item
 *  @param me_check If \a me_check is #UNCHECK (0), no checkmark will
 *         be displayed next to this item whereas if \a me_check 
 *		   is #CHECK (1), a checkmark will be displayed.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions
 *
 *  @sa mt_objc_change()
 *
 */

short
mt_menu_icheck(OBJECT *me_tree, short me_item, short me_check, short *global_aes)
{
	AES_PARAMS(31,2,1,1,0);
                    
	aes_intin[0] = me_item;
	aes_intin[1] = me_check;

	aes_addrin[0] = (long)me_tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
