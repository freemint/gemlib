/*
 *  $Id$
 */

#include "gem_aesP.h"

/** enables/disables menu items.
 *
 *  @param me_tree specifies the object tree of the menu to alter
 *  @param me_item is the object index of the menu item to modify
 *  @param me_enable should be set to #DISABLE (0) to disable the item or #ENABLE (1) to
 *         enable it.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_change()
 *
 */

short
mt_menu_ienable(OBJECT *me_tree, short me_item, short me_enable, short *global_aes)
{
	AES_PARAMS(32,2,1,1,0);
                    
	aes_addrin[0] = (long)me_tree;
	
	aes_intin[0] = me_item;
	aes_intin[1] = me_enable;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
