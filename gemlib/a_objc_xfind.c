/*
 *  $Id$
 */

#include "gem_aesP.h"

/** determines which object is found at a given coordinate.
 *
 *  @param tree specifies the object tree containing the objects to search
 *  @param start is the index of the object to start searshing from.
 *  @param depth specifies the depth in the tree to search (a value
 *         of 1 searches only first generation objects, a value of 2
 *         searches up to second generation objects, up to a maximum
 *         of 7 to search all objects).
 *  @param mx specify the x-coordinate to search at.
 *  @param my specify the y-coordinate to search at.
 *  @param global_aes global AES array
 *
 *  @return the object index of the object found at
 *          coordinates ( mx, my ) or -1 if no object is found.
 *
 *  @sa mt_objc_find()
 *
 *  The Difference between this function and objc_find is it, that not the
 *  normal rectangle of the OBJECT, but the outer rectangle is used, so that
 *  this function handles the border of the OBJECTs.
 *   
 *  @since The existence of this function can be checked with mt_appl_getinfo(5)
 *
 */

short 
mt_objc_xfind(OBJECT *tree, short start, short depth, short mx, short my, short *global_aes)
{
	AES_PARAMS(49,4,1,1,0);
                    
	aes_intin[0]  = start;
	aes_intin[1]  = depth;
	aes_intin[2]  = mx;
	aes_intin[3]  = my;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
