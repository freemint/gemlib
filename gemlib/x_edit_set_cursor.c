/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Alter settings: Absolute positioning of cursor
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param cursorpos specifies the new Absolute cursor position
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 */

void 
mt_edit_set_cursor( OBJECT *tree, short obj, char *cursorpos, short *global_aes )
{
	AES_PARAMS(217,2,0,2,0);
	
	aes_intin[0] = obj;
	aes_intin[1] = 4;
	
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)cursorpos;

	AES_TRAP(aes_params);
}
