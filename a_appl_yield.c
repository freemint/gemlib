#include "gem_aesP.h"

/** forces an AES process switch.
 *
 *  @param global_aes global AES array
 *  @return unknown
 *
 *  @since PC-GEM (as of version 2.0), MagiC (as of version 2.0)
 *
 *  @sa mt_evnt_timer()
 *
 *  @note Use mt_evnt_timer() with \a interval = 1L on other AES implementations.
 *  
 */

short
mt_appl_yield(short *global_aes)
{
	AES_PARAMS(17,0,1,0,0);

	AES_TRAP(aes_params);

	return aes_intout[0];
}
