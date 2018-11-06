#include "gem_aesP.h"

/** searches the current environment string for a specific variable.
 *
 *  @param result points to a character pointer which will be filled in
 *         with the address of the first character in the environment
 *         string following the string given by \a param. If the string
 *         given by \a param is not found, value will be filled in with
 *         NULL. For instance, suppose the current environment looked
 *         like this:  <tt> PATH=C:\\;D:\\;E:\\ </tt> \n
 *         A call made to mt_shel_envrn() with \a param pointing to the
 *         string \c 'PATH=' would set the pointer pointed to by value to
 *         the string <tt> 'C:\\;D:\\;E:\\' </tt> above.
 *  @param param see above
 *  @param global_aes global AES array
 *
 *  @return currently always returns 1.
 *
 *  @since All AES versions.
 *
 *  AES versions prior to 1.4 only accepted semi-colons as
 *  separators between multiple \c 'PATH=' arguments. Newer
 *  versions accept commas as well.
 *
 *  The character string pointed to by name should include the
 *  name of the variable and the equals sign.
 *
 */

short 
mt_shel_envrn(char **result, const char *param, short *global_aes)
{
	AES_PARAMS(125,0,1,2,0);
                    
	aes_addrin[0] = (long)result;
	aes_addrin[1] = (long)param;

	AES_TRAP(aes_params);
	
	/* Fix for the search for "PATH=" (bug of TOS)                       
	 *
	 * TOS has the nice bug, to read the system variable _bootdev ($446)
	 * - when initializing the environemnt - as a BYTE and not as a WORD
	 * So the boot device is added as a null byte into the PATH!
	 */
	
	if( *result && **result=='\0' && 
	     param[0]=='P' && param[1]=='A' && param[2]=='T' && param[3]=='H' && param[4]=='='
	   )
		(*result)++;

	return aes_intout[0];
}
