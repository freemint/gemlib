/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine settings: Colours
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param tcolour will be filled with the Text colour
 *  @param bcolour will be filled with the Background colour
 *  @param global_aes global AES array
 *
 *  @return 0 for error, else 1
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
mt_edit_get_colour( OBJECT *tree, short obj, short *tcolour, short *bcolour, short *global_aes )
{
	AES_PARAMS(216,2,3,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 2;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	*tcolour = aes_intout[1];
	*bcolour = aes_intout[2];

	return(aes_intout[0]);
}

