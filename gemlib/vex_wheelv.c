/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** establishes a routine in the wheel mouse interrupt
 *
 *  @param handle Device handle
 *  @param new address of the new routine
 *  @param old address of the old routine
 *
 *  @since Milan-VDI TOS 4.08
 *
 *  The routine will be
 *  called if the wheel of a mouse change; d0.w contain the wheel_number,
 *  d1.w contain the wheel_amount of the wheel from the mouse.
 *  The subroutine must save and restore modified registers and call the old
 *  interrupt routine. 
 *
 * 
 */

void
vex_wheelv (short handle, void *new, void **old)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
#endif
	
	vdi_control_ptr(7) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 134);
	
	*old = vdi_control_ptr(9);
}
