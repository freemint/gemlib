/*
 *  $Id$
 */

#include "gem_aesP.h"

/** changes the position of an object relative to
 *  other child objects of the same parent.
 *
 *  @param tree specifies the object tree
 *  @param object is the object to be moved
 *  @param new_pos specifies the new position of the object as
 *         follow:\n
 *         - #OO_LAST (-1) : Make object the last child.
 *         - #OO_FIRST (0) : Make object the first child.
 *         - 1 : Make object the second child.
 *         - 2 : etc...
 *  @param global_aes global AES array
 *
 *  @return 0 if an error occurred or non-zero otherwise.
 *
 *  @since All AES versions.
 *
 *  mt_objc_order() does not actually move structure elements in
 *  memory. It works by updating the OBJECT tree's ob_head,
 *  ob_tail, and ob_next fields to 'move' the OBJECT in the tree
 *  hierarchy.
 */

short 
mt_objc_order(OBJECT *tree, short object, short new_pos, short *global_aes)
{
	AES_PARAMS(45,2,1,1,0);
                    
	aes_intin[0]  = object;
	aes_intin[1]  = new_pos;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
