/*
 *   NOTE: requires NVDI version 3.x or higher
 */

#include "gem_vdiP.h"
#include "gemx.h"


void
vqt_advance32 (short handle, short ch, long *advx, long *advy)
{
	vdi_intin[0] = ch;

	VDI_TRAP (vdi_params, handle, 247, 0,2);

	*advx = *(long*)&vdi_ptsout[4];
	*advy = *(long*)&vdi_ptsout[6];
}
