/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** this function set the screen offset in raster lines from the begining
 *  of the logical screen.
 *
 *  @param handle Device handle
 *  @param offset
 *
 *  @since ???
 *
 *  @note this function is not descibe in any doc. Usage at your own risk!
 *
 */

void
v_offset (short handle, short offset)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, &offset, 0L, vdi_dummy, vdi_dummy );
		
	VDI_TRAP_ESC (vdi_params, handle, 5,101, 0,1);
}
