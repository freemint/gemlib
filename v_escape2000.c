#include "gem_vdiP.h"

/** In contrast to v_copies() this function sets the number of 
 *  copies additional to the "original" page.
 *
 *  @param handle Device handle
 *  @param times number of additional copies
 *
 *  @since depends on the driver
 *
 *  @note 
 *  Not every printer driver supports this call and since it has no return 
 *  values, you cannot inquire if it exists. Use v_copies()...
 *
 */

void
v_escape2000 (short handle, short times)
{
	short vdi_control[VDI_CNTRLMAX]; 

	VDI_PARAMS(vdi_control, &times, 0L, vdi_dummy, vdi_dummy );
	
	VDI_TRAP_ESC (vdi_params, handle, 5,2000, 0,1);
}
