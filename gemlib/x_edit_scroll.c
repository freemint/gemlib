/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Alter settings: Scroll positions
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param whdl Window handle or -1
 *  @param yscroll Vertical scroll offset in lines
 *  @param xscroll Horizontal scroll offset in pixels
 *  @param global_aes global AES array
 *
 *  @return 1 (OK) or 0 (Error)
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 *   With this one scrolls horizontally and vertically absolutely. This call 
 *   is required when a scroll bar or arrow has been clicked on.
 *   The window handle is required so that the rectangle list is taken into 
 *   consideration during scrolling.
 *   An error code will be returned if the number of lines has been exceeded.
 *
 */

short
mt_edit_scroll( OBJECT *tree, short obj, short whdl,
				long yscroll, short xscroll, short *global_aes )
{
	AES_PARAMS(217,6,1,1,0);

	aes_intin[0] = obj;
	aes_intin[1] = 9;
	aes_intin[2] = whdl;
	*(long *) (aes_intin+3) = yscroll;
	aes_intin[5] = xscroll;
	
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return(aes_intout[0]);
}
