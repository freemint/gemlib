/*
 *  $Id$
 */

#include "gem_aesP.h"

/** shifts a sub-menu that is attached to a menu
 *  item to align vertically with the specified object in the
 *  sub-menu.
 *
 *  @param me_flag should be set to MIS_SETALIGN (1) to modify the
 *         alignment of a sub-menu and its parent menu item. If \p me_flag
 *         is set to MIS_GETALIGN (0), no modifications will be made,
 *         however the sub-menu item index which is currently aligned
 *         with its parent menu item is returned.
 *  @param me_tree points to the object tree of the menu to alter
 *  @param me_imenu specifies the object within the submenu which will be
 *         aligned with menu item \p me_item
 *  @param me_item see above
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or the
 *          positive object index of the sub-menu item which is
 *          currently aligned with its parent menu item.
 *
 *  @since This function is only available with AES versions 3.30 and
 *         above.
 *
 *  @sa mt_menu_attach()
 *
 *  Generally, a sub-menu is aligned so that the currently
 *  selected sub-menu item is aligned with its parent menu.
 *
 */

short
mt_menu_istart(short me_flag, OBJECT *me_tree, short me_imenu, short me_item, short *global_aes)
{
	AES_PARAMS(38,3,1,1,0);
                    
	aes_intin[0] = me_flag;
	aes_intin[1] = me_imenu;
	aes_intin[2] = me_item;

	aes_addrin[0] = (long)me_tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
