/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Alter settings: Colours
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param tcolour -1 or text colour
 *  @param bcolour -1 or background colour
 *  @param global_aes global AES array
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  If one of the two attributes is to remain unchanged then -1 can be passed.
 *  If the editable object was opened previously, then one should generally 
 *  trigger a redraw when changing one of the attributes.
 *
 */

void 
mt_edit_set_colour( OBJECT *tree, short obj, short tcolour, short bcolour,
					short *global_aes )
{
	AES_PARAMS(217,4,0,1,0);
	
	aes_intin[0] = obj;
	aes_intin[1] = 2;
	aes_intin[2] = tcolour;
	aes_intin[3] = bcolour;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);
}

