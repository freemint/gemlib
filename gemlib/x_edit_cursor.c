/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Cursor on/off
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param whdl Window handle or -1
 *  @param show new cursor state or -1
 *  @param global_aes global AES array
 *
 *  @return the cursor-off counter.
 *
 *  The cursor is switched on (show == 1), switched off (show == 0) or 
 *  examined (show == -1).
 *  The call can be nested. 
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
mt_edit_cursor(OBJECT *tree, short obj, short whdl, short show, short *global_aes)
{
	AES_PARAMS(214,3,1,1,0);
	
	aes_intin[0]  = obj;
	aes_intin[1]  = whdl;
	aes_intin[2]  = show;
	aes_addrin[0] = (long)tree;

	AES_TRAP(aes_params);

	return(aes_intout[0]);
}

