/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** You can use this function to establish a function in the timer interrupt 
 *  (etv_timer).
 *
 *  @param handle Device handle
 *  @param time_addr address of the new timer routine
 *  @param otime_addr address of the old timer routine
 *  @param time_conv interrupt interval in ms
 *
 *  @since all VDI versions
 *
 *  The subroutine has to save and restore modified registers and call 
 *  the old timer routine
 *
 *
 */

void
vex_timv (short handle, void *time_addr, void **otime_addr, short *time_conv)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, time_conv, vdi_dummy );
	
	vdi_control_ptr(7) = time_addr;
	
	VDI_TRAP_00 (vdi_params, handle, 118);
	
	*otime_addr = vdi_control_ptr(9);
}
