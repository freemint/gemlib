/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** is required only for printers.
 *	It advances the printer page. This escape can
 *	be used instead of invoking a Clear Workstation
 *	function if it is desirable to retain the
 *	current printer display list while advancing to
 *	the next page.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_form_adv (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, 0L, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,20, 0,0);
}
