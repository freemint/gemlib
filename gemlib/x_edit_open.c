/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Open editable object
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param global_aes global AES array
 *
 *  @return 1, if OK
 *
 *  The number of lines and columns of text visible for the object size is 
 *  calculated, and corresponding pointers are created. Memory is then 
 *  requested for it.
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
mt_edit_open(OBJECT *tree, short obj, short *global_aes)
{
	AES_PARAMS(211,1,1,1,0);

	aes_intin[0]  = obj;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return( aes_intout[0] );
}

