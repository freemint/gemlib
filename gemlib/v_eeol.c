/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function erases the screen from the cursor position to the end of line
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_eeol (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,10, 0,0);
}
