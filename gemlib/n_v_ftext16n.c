/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
v_ftext16n (short handle, PXY pos, const WCHAR * wstr, short num)
{
	vdi_params.intin = (const short *)wstr;
	
	*(PXY*)vdi_ptsin = pos;

	VDI_TRAP (vdi_params, handle, 241, 1,num);

	vdi_params.intin = vdi_intin;
}
