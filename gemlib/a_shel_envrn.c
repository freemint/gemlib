/*
 *  $Id$
 */

#include "gem_aesP.h"

/** searches the current environment string for a specific variable.
 *
 *  @param result points to a character pointer which will be filled in
 *         with the address of the first character in the environment
 *         string following the string given by \p param. If the string
 *         given by \p param is not found, value will be filled in with
 *         NULL. For instance, suppose the current environment looked
 *         like this:  PATH=C:\\;D:\\;E:\\ \n
 *         A call made to mt_shel_envrn() with \p param pointing to the
 *         string 'PATH=' would set the pointer pointed to by value to
 *         the string 'C:\\;D:\\;E:\\' above.
 *  @param param 
 *  @param global_aes global AES array
 *
 *  @return currently always returns 1.
 *
 *  @since All AES versions.
 *
 *  AES versions prior to 1.4 only accepted semi-colons as
 *  separators between multiple 'PATH='arguments. Newer
 *  versions accept commas as well.
 *
 *  The character string pointed to by name should include the
 *  name of the variable and the equals sign.
 */

short 
mt_shel_envrn(char **result, const char *param, short *global_aes)
{
	AES_PARAMS(125,0,1,2,0);
                    
	aes_addrin[0] = (long)result;
	aes_addrin[1] = (long)param;

	AES_TRAP(aes_params);

	return aes_intout[0];
}


#ifdef shel_envrn
#undef shel_envrn
#endif
short 
shel_envrn(char **result, const char *param)
{
	return(mt_shel_envrn(result,param, aes_global));
}

