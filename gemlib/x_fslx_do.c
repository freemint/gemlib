/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** File selector dialog
 *
 *  @param title 
 *  @param path 
 *  @param pathlen 
 *  @param fname 
 *  @param fnamelen 
 *  @param patterns 
 *  @param filter 
 *  @param paths 
 *  @param sort_mode 
 *  @param flags 
 *  @param button 
 *  @param nfiles 
 *  @param pattern 
 *  @param global_aes global AES array
 *
 *  @return 
 *
 *  @since mt_appl_getinfo(7) give informations on mt_fslx_xx() functions availability
 *
 *  This function is a combination of mt_fslx_open() and mt_fslx_evnt(), but uses 
 *  a dialog box without a window.
 *
 *  see mt_fslx_open() and mt_fslx_evnt() for more details.
 *
 */

void *
mt_fslx_do(char *title, char *path, short pathlen, char *fname, short fnamelen, 
		   char *patterns, XFSL_FILTER filter, char *paths, short *sort_mode,
		   short flags, short *button, short *nfiles, char **pattern, short *global_aes)
{
	AES_PARAMS(194,4,4,6,2);

	aes_intin[0] = pathlen;
	aes_intin[1] = fnamelen;
	aes_intin[2] = *sort_mode;
	aes_intin[3] = flags;
	aes_addrin[0] = (long)title;
	aes_addrin[1] = (long)path;
	aes_addrin[2] = (long)fname;
	aes_addrin[3] = (long)patterns;
	aes_addrin[4] = (long)filter;
	aes_addrin[5] = (long)paths;

	AES_TRAP(aes_params);

	*button = aes_intout[1];
	*nfiles = aes_intout[2];
	*sort_mode = aes_intout[3];
	*pattern = (char *)aes_addrout[1];
	
	return (void *)aes_addrout[0];
}
