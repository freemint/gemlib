/*
 *  $Id$
 */

#include "gem_aesP.h"

/** 
 *
 *  @param sh_hmode
 *  @param sh_hfile
 *  @param sh_hkey
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 *  @sa 
 *
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

#ifdef shel_help
#undef shel_help
#endif
short 
shel_help(short sh_hmode, const char *sh_hfile, const char *sh_hkey)
{
	return(mt_shel_help(sh_hmode, sh_hfile, sh_hkey, aes_global));
}

