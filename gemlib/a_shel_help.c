/*
 *  $Id$
 */

#include "gem_aesP.h"

/** Call the help server
 *
 *  @param sh_hmode shall be #SHP_HELP (only value handled at the moment)
 *  @param sh_hfile Name of the help-file.
 *         if \a sh_hfile has an extension (for example \c 'test.hyp'), then on the basis
 *         of the extension ( \c .hyp in the example), the appropriate server in the list
 *         of the Helpserver is invoqued.\n
 *         if \a sh_hfile has no extension (for example \c 'test'), then the first server
 *         defined in the CNF file of the Helpservers is invoqued.
 *  @param sh_hkey Keyword, to which an assistance text is to be spent, or ZERO.
 *  @param global_aes global AES array
 *
 *  @return A return value of zero signals an error.
 *
 *  @since The presence of this function can be determined by mt_appl_getinfo() (Opcode 65).
 *
 *  @sa 
 *
 *  When the suitable help-server is found, then it is examined whether this is already active
 *  (as Accessory or also as concurrently started application). If this is the case, then the
 *  VA_START message is sent with \a sh_hfile and \a sh_hkey as arguments for command line.
 *  Otherwise, the suitable server is started with \a sh_hfile and \a sh_hkey parameters.
 */

short 
mt_shel_help(short sh_hmode, const char *sh_hfile, const char *sh_hkey, short *global_aes)
{
	AES_PARAMS(128,1,1,2,0);
                    
	aes_intin[0]  = sh_hmode;
	aes_addrin[0] = (long)sh_hfile;
	aes_addrin[1] = (long)sh_hkey;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
