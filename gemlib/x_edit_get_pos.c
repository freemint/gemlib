/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

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
 *  @return 
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
mt_edit_get_pos( OBJECT *tree, short obj, short *xscroll, long *yscroll,
				 char **cyscroll, char **cursorpos, short *cx, short *cy, short *global_aes)
{
	AES_PARAMS(216,2,6,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 5;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*xscroll = aes_intout[1];
	*yscroll = *((long *) (aes_intout+2));
	*cyscroll = (char *)aes_addrout[0];
	*cx = aes_intout[4];
	*cy = aes_intout[5];
	*cursorpos = (char *)aes_addrout[1];
}

