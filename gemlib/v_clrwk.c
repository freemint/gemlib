/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** erases the screen or - if the device is a printer or 
 *  plotter - advances the page and clears the printing buffer.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 *  @note With GEM VDI, you do not need to do a
 *        Clear Workstation after an Open Workstation
 *        because the display is cleared at Open
 *        Workstation.
 *
 */

void
v_clrwk (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, 0L, 0L);
#endif
	
	VDI_TRAP_00 (vdi_params, handle, 3);
}
