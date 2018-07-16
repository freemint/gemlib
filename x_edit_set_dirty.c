/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Alter settings: Dirty flag
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param dirty specifies the new dirty flag (0 or 1)
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  With this one can clear the Dirty flag when the text has been saved.
 *
 */

void 
mt_edit_set_dirty( OBJECT *tree, short obj, short dirty, short *global_aes)
{
	AES_PARAMS(217,3,0,1,0);

	aes_intin[0] = obj;
	aes_intin[1] = 7;
	aes_intin[2] = dirty;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);
}
