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
 *          coordinates ( \a mx, \a my ) or -1 if no object is found.
 *
 *  @since All AES versions.
 *
 *  @sa mt_objc_xfind()
 *
 *
 */

short 
mt_objc_find(OBJECT *tree, short start, short depth, short mx, short my, short *global_aes)
{
	AES_PARAMS(43,4,1,1,0);
                    
	aes_intin[0]  = start;
	aes_intin[1]  = depth;
	aes_intin[2]  = mx;
	aes_intin[3]  = my;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return aes_intout[0];
}
