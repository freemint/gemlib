/*
 *  $Id$
 */

#include "gem_aesP.h"

/** releases memory allocated by mt_rsrc_load() for an
 *  application's resource.
 *
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_rsrc_load()
 *
 *  mt_rsrc_free() should be called before an application which
 *  loaded a resource using mt_rsrc_load() exits.
 */

short 
mt_rsrc_free( short *global_aes)
{
	AES_PARAMS(111,0,1,0,0);

	AES_TRAP(aes_params);

	return aes_intout[0];
}
