/*
 *  $Id$
 */

#include "gem_aesP.h"

/** loads and allocates memory for the named
 *  resource file.
 *
 *  @param Name is a character pointer to a NULL-terminated GEMDOS
 *         file specification of the resource to load.
 *  @param global_aes global AES array
 *
 *  @return 1 if successful or zero if an error occurred.
 *
 *  @since All AES versions.
 *
 *  @sa mt_rsrc_free()
 *
 *  In addition to loading the resource, all OBJECT coordinates
 *  are converted from character based coordinates to screen
 *  coordinates.
 *
 */

short 
mt_rsrc_load(const char *Name, short *global_aes)
{
	AES_PARAMS(110,0,1,1,0);
                    
	aes_addrin[0] = (long)Name;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
