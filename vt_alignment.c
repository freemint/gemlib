#include "gem_vdiP.h"

/** 
 *
 *  @param handle Device handle
 *  @param dx x-offset from origin
 *  @param dy y-offset from origin
 *
 *  @since supported by all table drivers
 *
 *
 *
 */


void
vt_alignment (short handle, short dx, short dy)
{
	short vdi_control[VDI_CNTRLMAX]; 
	short vdi_intin[2];  
	 
	VDI_PARAMS(vdi_control, vdi_intin, 0L, vdi_dummy, vdi_dummy );
	
	vdi_intin[0] = dx;
	vdi_intin[1] = dy;
	
	VDI_TRAP_ESC (vdi_params, handle, 5,85, 0,2);
}
