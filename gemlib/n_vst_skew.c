/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vst_skew (short handle, short skew)
{
	vdi_intin[0] = skew;
	
	VDI_TRAP (vdi_params, handle, 253, 0,1);
	
	return vdi_intout[0];
}
