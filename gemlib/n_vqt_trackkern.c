/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_trackkern (short handle, long *x, long *y)
{
	VDI_TRAP_00 (vdi_params, handle, 234);
	
	*x = *(long*)&vdi_ptsout[0];
	*y = *(long*)&vdi_ptsout[2];
}
