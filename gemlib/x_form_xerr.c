/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** 
 *
 *  @param errcode 
 *  @param errfile 
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since 
 *
 *
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
