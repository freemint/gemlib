/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays a popup menu and returns the user's selection.
 *
 *  @param me_menu points to a MENU structure containing the popup menu
 *  @param me_xpos ... and ...
 *  @param me_ypos specify the location at which the upper-left corner of the
 *         starting object will be placed.
 *  @param me_mdata If the function returns a value of 1, the MENU structure
 *         pointed to by \p me_mdata will be filled in with the ending state
 *         of the menu (including the object the user selected).\n
 *         As of AES version 4.1, if menu.mn_scroll is set to
 *         SCROLL_LISTBOX (-1) when this function is called,
 *         a drop-down list box will be displayed instead of a popup
 *         menu.\n
 *         Dropdown list boxes will only display a scroll bar if at
 *         least eight entries exist. If you want to force the scroll
 *         bar to appear, pad the object with empty G_STRING objects
 *         with their DISABLED flag set.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or 1 if successful.
 *
 *  @since This function is only available with AES versions 3.30 and
 *         above.
 *
 *  @sa mt_menu_attach(), mt_menu_settings()
 *
 */

short
mt_menu_popup(MENU *me_menu, short me_xpos, short me_ypos, MENU *me_mdata, short *global_aes)
{
	AES_PARAMS(36,2,1,2,0);
                    
	aes_intin[0] = me_xpos;
	aes_intin[1] = me_ypos;

	aes_addrin[0] = (long)me_menu;
	aes_addrin[1] = (long)me_mdata;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
