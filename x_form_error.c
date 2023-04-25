#include "gem_aesP.h"
#include "mt_gemx.h"

/** displays a pre-defined error alert box to the user.
 *
 *  @param fmt
 *  @param error_code specifies a MS-DOS error code as follows:
 *               - #FERR_FILENOTFOUND : File Not Found
 *                                             The application can not find
 *                                             the folder or file that you
 *                                             tried to access.
 *               - #FERR_PATHNOTFOUND :  Path Not Found
 *                                             The application cannot find
 *                                             the folder or file that you
 *                                             tried to access.
 *               - #FERR_NOHANDLES  :  No More File Handles
 *                                             The application does not
 *                                             have room to open another
 *                                             document. To make room, close
 *                                             any open document that you do
 *                                             not need.
 *               - #FERR_ACCESSDENIED : Access Denied
 *                                             An item with this name
 *                                             already exists in the
 *                                             directory, or this item is
 *                                             set to read-only status.
 *               - #FERR_LOWMEM :      Insufficient Memory
 *                                             There is not enough memory
 *                                             for the application you just
 *                                             tried to run.
 *               - #FERR_BADENVIRON  : Invalid Environment
 *                                             There is not enough memory
 *                                             for the application you just
 *                                             tried to run.
 *               - #FERR_BADFORMAT :   Invalid Format
 *                                             There is not enough memory
 *                                             for the application you just
 *                                             tried to run.
 *               - #FERR_BADDRIVE :   Invalid Drive Specification
 *                                             The drive you specified does
 *                                             not exist.
 *               - #FERR_DELETEDIR :   Attempt To Delete Working
 *                                             Directory
 *                                             You cannot delete the folder
 *                                             in which you are working.
 *               - #FERR_NOFILES :     No More Files
 *                                             The application can not find
 *                                             the folder or file that you
 *                                             tried to access.
 *  @param global_aes global AES array
 *
 *  @return the exit button clicked as in
 *          mt_form_alert(). It is, however, insignifigant as all of the
 *          error alerts have only one button.
 *
 *  @since Geneva
 *
 *  @sa mt_form_alert()
 *
 *  @note The GEMDOS error number can be translated into the code expected
 *        in \a error_code by subtracting 31 from the absolute value of the
 *        GEMDOS error code.
 *  @note Not every GEMDOS error code has a matching alert box.
 *
 */

short
mt_x_form_error(const char *fmt, short error_code, short *global_aes)
{
	AES_PARAMS(0x7111,1,1,1,0);

	aes_intin[0] = error_code;
	aes_addrin[0] = (long)fmt;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
