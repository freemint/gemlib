/*
 *  $Id$
 */

#include "gem_aesP.h"

/** displays a pre-defined error alert box to the user.
 *
 *  @param error_code specifies a MS-DOS error code as follows:
\verbatim
               Name     GEMDOS Error # Error Message

               FERR_FILENOTFOUND  -33   2    File Not Found
                                             The application can not find
                                             the folder or file that you
                                             tried to access.

               FERR_PATHNOTFOUND  -34   3    Path Not Found
                                             The application cannot find
                                             the folder or file that you
                                             tried to access.

               FERR_NOHANDLES     -35   4    No More File Handles
                                             The application does not
                                             have room to open another
                                             document. To make room, close
                                             any open document that you do
                                             not need.

               FERR_ACCESSDENIED  -36   5    Access Denied
                                             An item with this name
                                             already exists in the
                                             directory, or this item is
                                             set to read-only status.

               FERR_LOWMEM        -39   8    Insufficient Memory
                                             There is not enough memory
                                             for the application you just
                                             tried to run.

               FERR_BADENVIRON    -41   10   Invalid Environment
                                             There is not enough memory
                                             for the application you just
                                             tried to run.

               FERR_BADFORMAT     -42   11   Invalid Format
                                             There is not enough memory
                                             for the application you just
                                             tried to run.

               FERR_BADDRIVE      -46   15   Invalid Drive Specification
                                             The drive you specified does
                                             not exist.

               FERR_DELETEDIR     -47   16   Attempt To Delete Working
                                             Directory
                                             You cannot delete the folder
                                             in which you are working.

               FERR_NOFILES       -49   18   No More Files
                                             The application can not find
                                             the folder or file that you
                                             tried to access.
\endverbatim
 *  @param global_aes global AES array
 *
 *  @return the exit button clicked as in
 *          form_alert(). It is, however, insignifigant as all of the
 *          error alerts have only one button.
 *
 *  @since All AES versions.
 *
 *  @sa mt_form_alert()
 *
 *  @note The GEMDOS error number can be translated into a MS-DOS
 *        code by subtracting 31 from the absolute value of the error
 *        code.
 *  @note Not every GEMDOS error code has a matching alert box.
 *
 */

short
mt_form_error(short error_code, short *global_aes)
{
	AES_PARAMS(53,1,1,0,0);

	aes_intin[0] = error_code;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
