/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Service editable object
 *
 *  @param tree RSC-tree of object
 *  @param obj Object number
 *  @param whdl Window handle or -1
 *  @param ev EVENT structure as for mt_wdlg_evnt(),
 *         mt_fnts_evnt(). The events are serviced by 
 *         the dialog if they are intended for the 
 *         associated window.
 *  @param errc Error code (-200 = text buffer full)
 *  @param global_aes global AES array
 *
 *  @return 0 if the passed events were not all
 *          serviced, say because the text buffer 
 *          was full or an error arose.
 *
 *  Events, i.e. mouse clicks and key presses, are forwarded to the editable 
 *  object and serviced by it if appropriate. When an event has been serviced, 
 *  the corresponding bit in the EVENT structure is cleared.
 *  The error code \p errc is present only from version 7 of the SLB onwards; 
 *  the binding in this library ensures that old SLB versions always return Nulls. 
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
mt_edit_evnt(OBJECT *tree, short obj, short whdl,
				EVNT *ev, long *errc, short *global_aes)
{
	AES_PARAMS(215,2,3,2,0);

	aes_intin[0]  = obj;
	aes_intin[1]  = whdl;
	aes_addrin[0] = (long)tree;
	aes_addrin[1] = (long)ev;
	*((long *) (aes_intout+1)) = 0L;	/* For old SLB */

	AES_TRAP(aes_params);

	*errc = *((long *) (aes_intout+1));

	return(aes_intout[0]);
}
