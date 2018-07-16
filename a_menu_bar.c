/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays a specialized OBJECT tree on the screen
 *  as the application menu. It can also be used to determine
 *  the owner of the currently displayed menu bar in
 *  a multitasking AES.
 *
 *  @param me_tree  is a pointer to an OBJECT tree which has been
 *         formatted for use as a system menu.
 *  @param me_mode  is a flag indicating the action to take as follows:
 *         - #MENU_REMOVE (0)    Erase the menu bar specified in \a me_tree.
 *         - #MENU_INSTALL (1)   Display the menu bar specified in \a me_tree.
 *         - #MENU_INQUIRE (-1)  Return the AES application identifier of
 *								the process which owns the currently
 *								displayed system menu. \a me_tree can be set
 *								to NULL. The AES version must be greater
 *								than 4.0 and mt_appl_getinfo() with #AES_INQUIRE
 *                              mode must
 *								indicate that this is feature is
 *								supported.
 *  @param global_aes global AES array
 *
 *  @return The return value depend on \a me_mode parameter as follow:
 *          - If \a me_mode is #MENU_REMOVE or #MENU_INSTALL, the return
 *          value indicates an error condition where >0 means no
 *          error and 0 means an error occurred.
 *          - if \a me_mode is #MENU_INQUIRE, mt_menu_bar() returns the application
 *          identifier of the process which owns the currently
 *          displayed menu bar.
 *
 *  @since  AES versions
 *
 *  @sa mt_menu_ienable(), mt_menu_icheck()
 *
 *  The safest way to redraw an application's menu bar is to
 *  redraw it only if you are sure it is currently the active
 *  menu bar. In a non-multitasking AES, this is a certainty,
 *  however, in a multitasking AES you should first inquire the
 *  menu bar's owner within the scope of a mt_wind_update() 
 *  call with #BEG_UPDATE mode to prevent the system from swapping
 *  active menu bars while in the process of redrawing.
 *
 *  @note it seems that some AES support other values for \a me_mode.
 *        These values are #MENU_GETMODE, #MENU_SETMODE, #MENU_UPDATE
 *        and #MENU_INSTL. TO BE COMPLETED.
 */

short
mt_menu_bar(OBJECT * me_tree, short me_mode, short *global_aes)
{
	AES_PARAMS(30,1,1,1,0);
                    
	aes_intin[0] = me_mode;

	aes_addrin[0] = (long)me_tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
