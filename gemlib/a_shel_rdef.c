/*
 *  $Id$
 */

#include "gem_aesP.h"

/** "Shell READ default" - default program query
 *
 *  @param lpcmd Pointer on a sufficiently dimensioned string for the name of the application.
 *  @param lpdir Pointer on a sufficiently dimensioned stringer for the path of the application
 *  @param global_aes global AES array
 *
 *  @return The return value is not at present well-known.
 *
 *  @since The presence of this function can be determined by mt_appl_getinfo() with mode
 *        #AES_PCGEM. Under MagiC-PC, this function is available since release 2.0
 *
 *  @sa 
 *
 *  The function makes it possible to inquire the program which is started
 *  after completion of the current (f.e. the Desktop).
 */

short 
mt_shel_rdef(char *lpcmd, char *lpdir, short *global_aes)
{
	AES_PARAMS(126,0,1,2,0);
                    
	aes_addrin[0] = (long)lpcmd;
	aes_addrin[1] = (long)lpdir;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
