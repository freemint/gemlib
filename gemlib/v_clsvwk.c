/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** closes a virtual workstation
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_clsvwk (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 101);
}
