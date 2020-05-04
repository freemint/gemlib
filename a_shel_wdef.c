#include "gem_aesP.h"

/** "Shell write default" - default program set
 *
 *  @param lpcmd
 *  @param lpdir
 *  @param global_aes global AES array
 *
 *  @return The return value is not at present well-known.
 *
 *  @since The presence of this function can be determined by mt_appl_getinfo() with mode
 *        #AES_PCGEM. Under PC-GEM, this function is available since release 2.0
 *
 *  @sa mt_shel_rdef()
 *  
 *  The function makes it possible to specify the application which
 *  is to be the default program (normally the Desktop).
 */

void mt_shel_wdef(const char *lpcmd, const char *lpdir, short *global_aes)
{
	AES_PARAMS(127,0,1,2,0);
   
	aes_addrin[0] = (long)lpcmd;
	aes_addrin[1] = (long)lpdir;

	AES_TRAP(aes_params);
}
