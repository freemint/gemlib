/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** This call switches reverse text output off
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_rvoff (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,14, 0,0);
}
