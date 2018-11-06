#include "gem_aesP.h"

/** converts an object's coordinates from
 *  character-based to pixel-based.
 *
 *  @param Tree specifies the OBJECT tree containing the object...
 *  @param Index ... to convert.
 *  @param global_aes global AES array
 *
 *  @return always returns a 0.
 *
 *  @since All AES versions.
 *
 *  @sa mt_rsrc_load(), mt_rsrc_rcfix()
 *
 *  All objects in '.RSC' files have their coordinates based on
 *  character positions rather than screen coordinates to allow
 *  an object tree to be shown in any resolution. This function
 *  converts those character coordinates to pixel coordinates
 *  based on the current screen resolution.
 *
 */

short 
mt_rsrc_obfix(OBJECT *Tree, short Index, short *global_aes)
{
	AES_PARAMS(114,1,1,1,0);
                    
	aes_intin[0]  = Index;
	aes_addrin[0] = (long)Tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
