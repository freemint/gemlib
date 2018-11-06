#include "gem_aesP.h"

/** removes an object from an object tree.
 *
 *  @param tree specifies the object tree of the object to delete.
 *  @param object is the object to be deleted.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_add()
 *
 *  This function does not move other objects in the tree
 *  structure, it simply unlinks the specified object from the
 *  object chain by updating the other object's ob_next,
 *  ob_head, and ob_tail structure members.
 *
 */

short 
mt_objc_delete(OBJECT *tree, short object, short *global_aes)
{
	AES_PARAMS(41,1,1,1,0);
                    
	aes_addrin[0] = (long)tree;
	aes_intin[0]  = object;

	AES_TRAP(aes_params);
	
	return aes_intout[0];
}
