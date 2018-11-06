#include "gem_vdiP.h"

/** draws an unfilled rectangle with rounded corners
 *
 *  @param handle Device handle
 *  @param pxy coordinates
 *
 *  @since all VDI versions
 *
 */

void
v_rbox (short handle, short pxy[])
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, 0L, pxy, vdi_dummy, vdi_dummy );

	VDI_TRAP_ESC (vdi_params, handle, 11,8, 2,0);
}
