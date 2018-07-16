/*
 *  $Id$
 */

#include "gem_aesP.h"

/** changes the text of a menu item.
 *
 *  @param me_tree specifies the object tree of the menu bar
 *  @param me_item specifies the object index of the menu item to change
 *  @param me_text points to a NULL-terminated character string containing the
 *         new text.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *
 */

short
mt_menu_text(OBJECT *me_tree, short me_item, char *me_text, short *global_aes)
{
	AES_PARAMS(34,1,1,2,0);
                    
	aes_intin[0] = me_item;

	aes_addrin[0] = (long)me_tree;
	aes_addrin[1] = (long)me_text;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
