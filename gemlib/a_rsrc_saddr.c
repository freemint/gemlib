/*
 *  $Id$
 */

#include "gem_aesP.h"

/** sets the address of a resource element.
 *
 *  @param Type specifies the type of resource element to set as
 *         defined under mt_rsrc_gaddr()
 *  @param Index specifies the index of the element to modify (0 based)
 *  @param Address specifies the actual address that will be placed in
 *         the appropriate data structure.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_rsrc_gaddr(), mt_rsrc_load()
 *
 *  In most cases, direct manipulation of the structures
 *  involved is quicker and easier than using this call.
 *
 */

short 
mt_rsrc_saddr(short Type, short Index, void *Address, short *global_aes)
{
	AES_PARAMS(113,2,1,1,0);
                    
	aes_intin[0]  = Type;
	aes_intin[1]  = Index;
	aes_addrin[0] = (long)Address;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
