#include "gem_vdiP.h"

/** After calling this function text will be displayed reverse
 *
 *  @param handle Device handle
 *
 *  @since all VDI versions
 *
 */

void
v_rvon (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, 0L, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,13, 0,0);
}
