/*
 *  $Id$
 */

#include "gem_vdiP.h"
#include "mt_gemx.h"

/** This function exists only for compatibility reasons. It switches off the 
 *  special treatment of v_bez()/v_bez_fill().
 *
 *  @param handle Device handle
 *
 *  @since since NVDI 2.10
 *
 *
 *
 */

void
v_bez_off (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy);
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 11,13, 0,0);
}
