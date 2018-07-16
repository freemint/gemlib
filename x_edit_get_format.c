/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Examine settings: Formating
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param tabwidth will be filled by the tabulator width.\n
 *         [option CHECK_NULLPTR] tabwidth may be NULL
 *  @param autowrap will be filled by the autowrap information:
 *         - \p autowrap > 0: Pixel width for auto line wrap (generally == object width)
 *         - \p autowrap = 0: No wrapping, but horiz. scrolling
 *         .
 *         [option CHECK_NULLPTR] autowrap may be NULL
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
mt_edit_get_format( OBJECT *tree, short obj,
					short *tabwidth, short *autowrap, short *global_aes )
{
	AES_PARAMS(216,2,3,1,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = 1;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (tabwidth)
#endif
	*tabwidth = aes_intout[1];
#if CHECK_NULLPTR
	if (autowrap)
#endif
	*autowrap = aes_intout[2];

	return(aes_intout[0]);
}

