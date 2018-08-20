/*
 *  $Id$
 */

#include "gem_aesP.h"

/** registers desk accessories in the 'Desk'
 *  menu and renames MultiTOS applications which appear there.
 *
 *  @param ap_id specifies the application identifier of the
 *         application to register
 *  @param me_text points to a NULL-terminated
 *         string containing the title which is to appear in the
 *         'Desk' menu for the accessory or application.
 *  @param global_aes global AES array
 *
 *  @return -1 if an error occurred or the menu identifier otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa 
 *
 *  @note Applications other than desk accessories should not call
 *        this function unless they are running under MultiTOS.
 *
 *  @note If \a ap_id is set to #REG_NEWNAME (-1) then the process name
 *        given in \a me_text will be used as the new process name. The
 *        new process name should be exactly eight characters
 *        terminated with a NULL. Pad the string with space
 *        characters if necessary.
 *
 *  Desk accessories should store the return value as this is
 *  the value that will be included with future #AC_OPEN
 *  messages to identify the accessory.\n
 *  Applications running under MultiTOS may use this function
 *  to provide a more functional title for the 'Desk' menu than
 *  the program's filename.\n
 *  Calling mt_menu_register() with a parameter of #REG_NEWNAME is
 *  used to change the internal process name of the application
 *  returned by mt_appl_find() and mt_appl_search(). This is useful
 *  if you know another process will attempt to find your
 *  application as a specific process name and the user may
 *  have renamed your application filename (normally used as
 *  the process name).
 */

short
mt_menu_register(short ap_id, const char *me_text, short *global_aes)
{
	AES_PARAMS(35,1,1,1,0);
                    
	aes_intin[0] = ap_id;
	aes_addrin[0] = (long)me_text;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
