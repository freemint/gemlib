/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** moves the cursor right. If the cursor is already in the 
 *  last column, nothing happens.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_curright (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, 0L, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,6, 0,0);
}
