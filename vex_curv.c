#include "gem_vdiP.h"

/** establishes a routine in the mouse interrupt
 *
 *  @param handle Device handle
 *  @param newhdlr address of the new routine
 *  @param old address of the old routine
 *
 *  @since all VDI versions
 *
 *  The routine will be
 *  called if the mouse is moved and d0.w/d1.w contain the coordinates of the mouse 
 *  cursor. The subroutine must save and restore modified registers and call the old 
 *  interrupt routine. 
 *  
 *  Please note that this interrupt routine is called after the one installed by 
 *  vex_motv(). In contrast to the preceding routine, the mouse coordinates have 
 *  been clipped.
 *
 *
 */

void
vex_curv (short handle, void *new, void **old)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy);
	
	vdi_control_ptr(0, void *) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 127);
	
	if (old)
		*old = vdi_control_ptr(1, void *);
}
