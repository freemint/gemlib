/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** establishes a routine in the mouse interrupt
 *
 *  @param handle Device handle
 *  @param new address of the new routine
 *  @param old address of the old routine
 *
 *  @since all VDI versions
 *
 *  The routine will be
 *  called if the mouse is moved and d0.w/d1.w contain the coordinates of the mouse 
 *  cursor. The subroutine must save and restore modified registers and call the old 
 *  interrupt routine. 
 *
 *
 */

void
vex_motv (short handle, void *new, void **old)
{
#if USE_LOCAL_VDIPB
	short vdi_control[VDI_CNTRLMAX]; 
	VDIPB vdi_params =               
	{                                
		&vdi_control[0],             /* vdi_control */
		0L, 						 /* vdi_intin	*/
		0L, 						 /* vdi_ptsin	*/
		0L, 						 /* vdi_intout  */
		0L							 /* vdi_ptsout  */
	};
#endif
	
	vdi_control_ptr(7) = new;
	
	VDI_TRAP_00 (vdi_params, handle, 126);
	
	*old = vdi_control_ptr(9);
}
