/*
 *  $Id$
 */

#include "gemx.h"
#include "gem_aesP.h"

/** Create editable object
 *
 *  @param global_aes global AES array
 *
 *  @return a descriptor for any further
 *          actions, or NULL if an error has 
 *          occurred (not enough memory).
 *          The descriptor must be entered as
 *          ob_spec into the object.
 *
 *  The corresponding descriptor is created (memory is reserved), but the 
 *  editor has not been opened yet. One can now alter several settings with
 *  mt_edit_set(). The default settings are:
 *  - System font, 10 pt
 *  - Black on white
 *  - No line wrap
 *  - Tabulator width 64 pixels
 *
 *  @since from MagiC 5.20 onwards. As it is 
 *         implemented as part of the shared library (SLB or SharedLib), 
 *         one only needs to open the library with:\n
 *         <pre>Slbopen("EDITOBJC.SLB", NULL, 0L, &slb, &slbexec);</pre>
 *         The library installs a new AES object-type G_EDIT (37)
 *         as well as the AES functions mt_edit_xx().
 *
 */

XEDITINFO *
mt_edit_create( short *global_aes )
{
	AES_PARAMS(210,0,0,0,0);

	AES_TRAP(aes_params);

	return( (XEDITINFO *) aes_addrout[0] );
}
