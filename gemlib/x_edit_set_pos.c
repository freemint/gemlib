/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** 
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param xscroll 
 *  @param yscroll 
 *  @param cyscroll 
 *  @param cursorpos 
 *  @param cx 
 *  @param cy 
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
mt_edit_set_pos( OBJECT *tree, short obj, short xscroll, long yscroll,
				 char *cyscroll, char *cursorpos, short cx, short cy, short *global_aes)
{
	AES_PARAMS(217,7,0,3,0);

	aes_intin[0] = obj;
	aes_intin[1] = 5;
	aes_intin[2] = xscroll;
	*(long *) (aes_intin+3) = yscroll;
	aes_intin[5] = cx;
	aes_intin[6] = cy;
	
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)cyscroll;
	aes_addrin[2] = (long)cursorpos;

	AES_TRAP(aes_params);
}
