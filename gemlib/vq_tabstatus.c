/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This escape returns the availability status
 *  of a graphics tablet, mouse, joystick, or
 *  other similar device.
 *
 *  @param handle Device handle
 *
 *  @return Tablet status :
 *          - 0 = tablet not available
 *          - 1 = tablet available
 *
 *  @since all VDI versions
 *
 */

short
vq_tabstatus (short handle)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intout[1]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_intout, vdi_dummy );
#endif
	
	VDI_TRAP_ESC (vdi_params, handle, 5,16, 0,0);
	
	return vdi_intout[0];
}
