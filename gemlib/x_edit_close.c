/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** 
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param global_aes global AES array
 *
 *  The object-size-dependent management structures are closed and the  
 *  memory used is released. The descriptor itself, though, is preserved.
 *  Text management is now no longer possible.
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
mt_edit_close(OBJECT *tree, short obj, short *global_aes)
{
	AES_PARAMS(212,1,0,1,0);

	aes_intin[0]  = obj;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);
}
