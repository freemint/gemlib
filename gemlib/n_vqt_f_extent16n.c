/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_f_extent16n (short handle, const WCHAR * wstr, short num, short extent[])
{
	vdi_params.intin  = (const short *)wstr;
	vdi_params.ptsout = extent;

	VDI_TRAP (vdi_params, handle, 240, 0,num);

	vdi_params.intin  = vdi_intin;
	vdi_params.ptsout = vdi_ptsout;
}
