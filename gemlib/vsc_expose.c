/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param state
 *
 *  @since all VDI versions
 *
 *  @sa
 *
 *
 *
 */

void
vsc_expose (short handle, short state)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, &state, 0L, 0L, 0L);
#else
	vdi_intin[0] = state;
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,93, 0,1);
}
