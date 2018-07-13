/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** installs a routine which is called when a mouse 
 *  button is pressed
 *
 *  @param handle Device handle
 *  @param new address of the new routine
 *  @param old address of the old routine
 *
 *  @since all VDI versions
 *
 *  Register d0.w contains the button state. The subroutine must 
 *  save and restore modified registers and call the old status routine.
 *
 */

void
vex_butv (short handle, void *newhdlr, void **old)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
	
	vdi_control_ptr(0, void *) = newhdlr;
	
	VDI_TRAP_00 (vdi_params, handle, 125);
	
	if (old)
		*old = vdi_control_ptr(1, void *);
}
