/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** returns the length of the PRN_SETTINGS structure
 *
 *  @param global_aes global AES array
 *
 *  @return length of the PRN_SETTINGS structure in bytes
 *
 *  @since mt_appl_getinfo(7) give informations on mt_pdlg_xx() functions availability
 *
 */

long
mt_pdlg_get_setsize(short *global_aes)
{
	long	l;
	
	AES_PARAMS(204,1,2,0,0);

	aes_intin[0] = 0;

	AES_TRAP(aes_params);

	l = *(long *) &aes_intout[0];
	
	return l;
}
