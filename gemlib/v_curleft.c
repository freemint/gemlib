/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** The cursor is moved left. If it is already in
 *  the first column, nothing happens.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_curleft (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,7, 0,0);
}
