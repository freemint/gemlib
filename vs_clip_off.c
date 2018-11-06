#include "gem_vdiP.h"

/** same as vs_clip(handle,0,dummy)
 *
 *  @param handle Device handle
 *
 */

void
vs_clip_off (short handle)
{
	short vdi_control[VDI_CNTRLMAX]; 
	static short vdi_intin[1] = {0};   
	static short vdi_ptsin[4] = {0,0,0,0};  
	 
	VDI_PARAMS(vdi_control, vdi_intin, vdi_ptsin, vdi_dummy, vdi_dummy );
	
	VDI_TRAP (vdi_params, handle, 129, 2,1);
}
