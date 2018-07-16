/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This function for printer or plotter drivers clears the printing buffer 
 *  (and deletes all previous commands). In contrast to v_clrwk() it does 
 *  not advance the page.
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 *  This function should be called if the user interrupts printing while your 
 *  application generates the page.
 *
 */

void
v_clear_disp_list (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,22, 0,0);
}
