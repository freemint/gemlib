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
vex_butv (short handle, void *new, void **old)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L,                          /* vdi_intin   */
		0L,                          /* vdi_ptsin   */
		0L,                          /* vdi_intout  */
		0L                           /* vdi_ptsout  */
	};
#endif
	
	vdi_control_ptr(7) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 125);
	
	*old = vdi_control_ptr(9);
}
