/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** moves the cursor down one row. If the cursor is already in 
 *  the last row, nothing happens.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_curdown (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, 0L, 0L );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,5, 0,0);
}
