/*
 *  $Id$
 */

#include "gem_vdiP.h"

/** switches the mouse cursor off
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 *  @note Use mt_graf_mouse() to switch the cursor on or off.
 *
 */

void
v_hide_c (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_00 (vdi_params, handle, 123);
}
