/*
 *  $Id$
 */

#include "gem_aesP.h"

/** fixes up coordinates and memory pointers of
 *  raw resource data in memory.
 *
 *  @param rc_header is a pointer to an Atari Resource Construction
 *         Set (or compatible) resource file header in memory.
 *  @param global_aes global AES array
 *
 *  @return 0 if unsuccessful or non-zero otherwise.
 *
 *  @since Available only in AES versions 4.0 and greater. The
 *         presence of this call should also be checked for using
 *         mt_appl_getinfo().
 *
 *  @sa mt_rsrc_obfix()
 *
 *  If a resource has already been loaded with mt_rsrc_load() it
 *  must be freed by mt_rsrc_free() prior to this call. In
 *  addition, resources identified with this call must likewise
 *  be freed before program termination or another resource
 *  file is needed.
 *
 */

short 
mt_rsrc_rcfix(void *rc_header, short *global_aes)
{
	AES_PARAMS(115,0,1,1,0);
                    
	aes_addrin[0] = (long)rc_header;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
