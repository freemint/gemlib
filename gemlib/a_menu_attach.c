/*
 *  $Id$
 */

#include "gem_aesP.h"

/** allows an application to attach, change, or
 *  remove a sub-menu. It also allows the application to
 *  inquire information regarding a currently defined sub-menu.
 *
 *  @param me_flag indicates the action the application desires as
 *         follows:
 *         - ME_INQUIRE (0)  Return information on a sub-menu attached
 *                           to the menu item designated by \p me_tree and
 *                           \p me_item in \p me_mdata.
 *         - ME_ATTACH (1)   Attach or change a sub-menu. \p me_mdata should
 *                           be initialized by the application.
 *                           \p me_tree and \p me_item should be the OBJECT pointer
 *                           and index to the menu which is to have the
 *                           sub-menu attached. If \p me_mdata is NULLPTR, any
 *                           sub-menu attached will be removed.
 *         - ME_REMOVE (2)   Remove a sub-menu. \p me_tree and \p me_item should be
 *                           the OBJECT pointer and index to the menu
 *                           item which a sub-menu was attached to.
 *                           \p me_mdata should be NULLPTR.
 *  @param me_tree see above
 *  @param me_item see above
 *  @param me_mdata see above
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred and the
 *			sub-menu could not be attached or 1 if the operation was
 *			successful.
 *
 *  @since This function is only available from AES version 3.30 and
 *         above. In AES versions 4.0 and greater, mt_appl_getinfo()
 *         should be used to determine its exact functionality.
 *
 *  AES versions supporting mt_menu_attach() less than 4.1 contain
 *	a bug which causes the AES to crash when changing or
 *	removing a sub-menu attachment.
 *	At present, if you wish to attach a scrolling menu, the
 *	menu items must be G_STRING's.
 *	The ob_x and ob_y fields of the root menu object should
 *	always be set to 0 prior to making the menu_attach() call.
 *	In addition, under AES 3.40, no more than one scrolling
 *	sub-menu should be contained in each tree.
 *
 *  If a menu bar having attachments is removed with
 *  mt_menu_bar( NULL, MENU_REMOVE ) those attachments
 *  are removed by the system and must be reattached with this
 *  call if the menu is redisplayed at a later time.
 *  Several recommendations regarding sub-menus should be
 *  adhered to:
 *  -# Menu items which will have sub-menus attached to them
 *     should be padded with blanks to the end of the menu.
 *  -# Menu items which will have sub-menus attached to them
 *     should not have a keyboard equivalent.
 *  -# Sub-menus will display faster if a byte-boundary is
 *     specified.
 *  -# Sub-menus will be shifted vertically to align the start
 *     object with the main menu item which it is attached to.
 *  -# Sub-menus will always be adjusted to automatically fit
 *     on the screen.
 *  -# There can be a maximum of 64 sub-menu attachments per
 *     process (attaching a sub-menu to more than one menu
 *     item counts as only one attachment).
 *  -# Do not attach a sub-menu to itself.
 *  -# As a user-interface guideline, there should only be one
 *     level of sub-menus, though it is possible to have up to
 *     four levels currently.
 *  -# mt_menu_istart() works only on sub-menus attached with
 *     mt_menu_attach().
 *
 *  @sa mt_menu_istart(), mt_menu_settings(), mt_menu_popup()
 *
 */

short
mt_menu_attach(short me_flag, OBJECT *me_tree, short me_item, MENU *me_mdata, short *global_aes)
{
	AES_PARAMS(37,2,1,2,0);
                    
	aes_intin[0] = me_flag;
	aes_intin[1] = me_item;
	
	aes_addrin[0] = (long)me_tree;
	aes_addrin[1] = (long)me_mdata;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
