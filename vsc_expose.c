#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param state ???
 *
 *  @since all VDI versions
 *
 *
 *
 */

void
vsc_expose (short handle, short state)
{
	short vdi_control[VDI_CNTRLMAX]; 
	
	VDI_PARAMS(vdi_control, &state, 0L, vdi_dummy, vdi_dummy);
	
	VDI_TRAP_ESC (vdi_params, handle, 5,93, 0,1);
}
