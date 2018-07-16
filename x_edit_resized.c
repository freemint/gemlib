/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Alter settings: Object size
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param oldrh Old net height of object \n
 *         [option CHECK_NULLPTR] oldrh may be NULL
 *  @param newrh New net height of object \n
 *         [option CHECK_NULLPTR] newrh may be NULL
 *  @param global_aes global AES array
 *
 *  @return 1 (OK) or 0 (error)
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *  For changes of the object size the editable object must release and reserve 
 *  memory. Thus it is possible that in extreme circumstances the operation 
 *  fails due to a shortage of memory. In that case the return value is 0.
 *  So that the calling program can execute a correct redraw, the previous and 
 *  new actual height is returned. In fact it means here the number of visible 
 *  lines multiplied by the line height, i.e. the object height without the 
 *  unused bottom white border
 */

short
mt_edit_resized( OBJECT *tree, short obj, short *oldrh, short *newrh, short *global_aes)
{
	AES_PARAMS(217,2,3,1,0);

	aes_intin[0] = obj;
	aes_intin[1] = 6;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

#if CHECK_NULLPTR
	if (oldrh)
#endif
	*oldrh = aes_intout[1];
#if CHECK_NULLPTR
	if (newrh)
#endif
	*newrh = aes_intout[2];
	
	return(aes_intout[0]);
}
