/*
 *  $Id$
 */

#include "gem_aesP.h"
#include "mt_gemx.h"

/** Remove editable object
 *
 *  @param xi Pointer to a XEDITINFO structure returned by mt_edit_create()
 *  @param global_aes global AES array
 *
 *  The descriptor is released. If the object is to be used further then the 
 *  object type has to be placed back on G_BOX.
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
mt_edit_delete( XEDITINFO *xi, short *global_aes)
{
	AES_PARAMS(213,0,0,1,0);

	aes_addrin[0] = (long)xi;

	AES_TRAP(aes_params);
}
