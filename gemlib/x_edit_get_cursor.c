/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Examine settings: Absolute cursor position
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param cursorpos will be filled with the Cursor position in text
 *  @param global_aes global AES array
 *
 *  @return 0 (error) or 1 (OK)
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 */

short 
mt_edit_get_cursor( OBJECT *tree, short obj, char **cursorpos, short *global_aes )
{
	AES_PARAMS(216,2,1,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 4;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*cursorpos = (char *)aes_addrout[0];
	
	return(aes_intout[0]);
}

