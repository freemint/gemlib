/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Examine settings: Dirty flag
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param global_aes global AES array
 *
 *  @return the dirty flag (0 or 1)
 *
 *  With this one can ascertain whether the text was altered in the meantime.
 *  The flag can be cleared again with mt_edit_set_dirty() or mt_edit_set_buf().
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
mt_edit_get_dirty( OBJECT *tree, short obj, short *global_aes )
{
	AES_PARAMS(216,2,1,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 7;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return(aes_intout[0]);
}

