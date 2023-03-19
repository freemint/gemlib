#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine settings: Selected region
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param bsel will be filled with a pointer to the start of selected region,
 *         or NULL if no region is selected. \n
 *         [option CHECK_NULLPTR] bsel may be NULL
 *  @param esel will be filled with a pointer to the character after the end
 *         of the selected region \n
 *         [option CHECK_NULLPTR] esel may be NULL
 *  @param global_aes global AES array
 *
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
mt_edit_get_sel( OBJECT *tree, short obj, char **bsel, char **esel, short *global_aes)
{
	AES_PARAMS(216,2,0,1,2);

	aes_intin[0]  = obj;
	aes_intin[1]  = 8;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (bsel)
#endif
	*bsel = (char *)aes_addrout[0];
#if CHECK_NULLPTR
	if (esel)
#endif
	*esel = (char *)aes_addrout[1];
}
