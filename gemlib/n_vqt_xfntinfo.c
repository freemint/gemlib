/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


short
vqt_xfntinfo (short handle, short flags, short id, short index, XFNT_INFO *info)
{
	info->size = sizeof (XFNT_INFO);
	vdi_intin    [0] = flags;
	vdi_intin    [1] = id;
	vdi_intin    [2] = index;
	vdi_intin_ptr(3) = info;
	
	VDI_TRAP (vdi_params, handle, 229, 0,5);
	
	return vdi_intout[1];
}
