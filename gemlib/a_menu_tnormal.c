/*
 *  $Id$
 */

#include "gem_aesP.h"

/** highlights/un-highlights a menu-title.
 *
 *  @param me_tree specifies the object tree of the menu
 *  @param me_item specifies the object index of the title to change
 *  @param me_normal should be set
 *         to #HIGHLIGHT (0) to display the title in reverse
 *         (highlighted) or #UNHIGHLIGHT (1) to display it normally
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since  AES versions
 *
 *  This call is usually called by an application after
 *  a #MN_SELECTED message is received and processed to return
 *  the menu title to normal.
 *
 */

short
mt_menu_tnormal(OBJECT *me_tree, short me_item, short me_normal, short *global_aes)
{
	AES_PARAMS(33,2,1,1,0);
                    
	aes_intin[0] = me_item;
	aes_intin[1] = me_normal;

	aes_addrin[0] = (long)me_tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
