/*
 *  $Id$
 */

#include "gem_aesP.h"

/** establishes a child object's relationship to its parent.
 *
 *  @param tree specifies the object tree to modify.
 *  @param parent specify the parent object.
 *  @param child specify the child object to update.
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_order(), mt_objc_delete()
 *
 *  In order for this function to work, the object to be added
 *  must be already be a member of the OBJECT array. This
 *  function simply updates the ob_next, ob_head, and ob_tail
 *  structure members of OBJECTs in the object tree. These
 *  fields should be initialized to #NIL (0) in the child to be
 *  added.
 *
 */

short 
mt_objc_add(OBJECT *tree, short parent, short child, short *global_aes)
{
	AES_PARAMS(40,2,1,1,0);
                    
	aes_intin[0]  = parent;
	aes_intin[1]  = child;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
