/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_real_extent (short handle, short x, short y, char *string, short extent[])
{
	register short n = vdi_str2array (string, vdi_intin);
	
	vdi_params.ptsout = extent;
	
	vdi_ptsin[0] = x;
	vdi_ptsin[1] = y;
	
	VDI_TRAP_ESC (vdi_params, handle, 240,4200, 1,n);
	
	vdi_params.ptsout = vdi_ptsout;
}
