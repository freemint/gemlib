/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** extended function that display a pre-defined error alert box to the user.
 *
 *  @param errcode is the error code. This code may be either in MS-DOS format
 *         (a positive interger, as expected by mt_form_error()), or directly
 *         the GEMDOS/BIOS error code (negative value returned by a GEMDOS or
 *         a BIOS function)
 *  @param errfile path of the file that causes the error (this string will
 *         appear in the alert box), or 0L (the parameter will be ignored),
 *         or -1L (the alert box will display "program returned:" in place of
 *         the filename).
 *  @param global_aes global AES array
 *
 *  @return the exit button clicked as in
 *          mt_form_alert(). It is, however, insignifigant as all of the
 *          error alerts have only one button.
 *
 *  @since MagiC 2.0
 *
 *  @sa mt_form_error()
 *
 *  @note if \a errcode is 0 (EOK, no error) or -68 (EBREAK, program aborted
 *        by the user by pressing CTRL-C keys), then no form is display.
 *
 */

short 
mt_form_xerr(long errcode, char *errfile, short *global_aes)
{
	unsigned short *i = (unsigned short *)&errcode;
	
	AES_PARAMS(136,2,1,1,0);
                    
	aes_intin[0] = i[1];
	aes_intin[1] = i[0];

	aes_addrin[0] = (long)errfile;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
